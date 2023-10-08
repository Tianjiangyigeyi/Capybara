#include "precomp.h"
#include "SceneRenderer.h"

#include "Renderer.h"
#include "Capybara/Renderer/Renderer2D.h"
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Capybara {

	struct SceneRendererData
	{
		const Scene* ActiveScene = nullptr;
		struct SceneInfo
		{
			Camera SceneCamera;

			// Resources
			Ref<MaterialInstance> SkyboxMaterial;
			Environment SceneEnvironment;
		} SceneData;

		Ref<Texture2D> BRDFLUT;
		Ref<Shader> CompositeShader;

		Ref<RenderPass> GeoPass;
		Ref<RenderPass> CompositePass;

		struct DrawCommand
		{
			Ref<Mesh> Mesh;
			Ref<MaterialInstance> Material;
			glm::mat4 Transform;
		};
		std::vector<DrawCommand> DrawList;

		// Grid
		Ref<MaterialInstance> GridMaterial;

		SceneRendererOptions Options;
	};

	static SceneRendererData s_Data;

	void SceneRenderer::Init()
	{
		FramebufferSpecification geoFramebufferSpec;
		geoFramebufferSpec.Width = 1280;
		geoFramebufferSpec.Height = 720;
		geoFramebufferSpec.Format = FramebufferFormat::RGBA16F;
		geoFramebufferSpec.Samples = 8;
		geoFramebufferSpec.ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };

		RenderPassSpecification geoRenderPassSpec;
		geoRenderPassSpec.TargetFramebuffer = Capybara::Framebuffer::Create(geoFramebufferSpec);
		s_Data.GeoPass = RenderPass::Create(geoRenderPassSpec);

		FramebufferSpecification compFramebufferSpec;
		compFramebufferSpec.Width = 1280;
		compFramebufferSpec.Height = 720;
		compFramebufferSpec.Format = FramebufferFormat::RGBA8;
		compFramebufferSpec.ClearColor = { 0.5f, 0.1f, 0.1f, 1.0f };

		RenderPassSpecification compRenderPassSpec;
		compRenderPassSpec.TargetFramebuffer = Capybara::Framebuffer::Create(compFramebufferSpec);
		s_Data.CompositePass = RenderPass::Create(compRenderPassSpec);

		s_Data.CompositeShader = Shader::Create("assets/shaders/SceneComposite.glsl");
		s_Data.BRDFLUT = Texture2D::Create("assets/textures/BRDF_LUT.tga");

		// Grid
		auto gridShader = Shader::Create("assets/shaders/Grid.glsl");
		s_Data.GridMaterial = MaterialInstance::Create(Material::Create(gridShader));
		float gridScale = 16.025f, gridSize = 0.025f;
		s_Data.GridMaterial->Set("u_Scale", gridScale);
		s_Data.GridMaterial->Set("u_Res", gridSize);
	}

	void SceneRenderer::SetViewportSize(uint32_t width, uint32_t height)
	{
		s_Data.GeoPass->GetSpecification().TargetFramebuffer->Resize(width, height);
		s_Data.CompositePass->GetSpecification().TargetFramebuffer->Resize(width, height);
	}

	void SceneRenderer::BeginScene(const Scene* scene)
	{
		CPBR_CORE_ASSERT(!s_Data.ActiveScene, "");

		s_Data.ActiveScene = scene;

		s_Data.SceneData.SceneCamera = scene->m_Camera;
		s_Data.SceneData.SkyboxMaterial = scene->m_SkyboxMaterial;
		s_Data.SceneData.SceneEnvironment = scene->m_Environment;
	}

	void SceneRenderer::EndScene()
	{
		CPBR_CORE_ASSERT(s_Data.ActiveScene, "");

		s_Data.ActiveScene = nullptr;

		FlushDrawList();
	}

	void SceneRenderer::SubmitEntity(Entity* entity)
	{
		// TODO: Culling, sorting, etc.

		auto mesh = entity->GetMesh();
		if (!mesh)
			return;

		s_Data.DrawList.push_back({ mesh, entity->GetMaterial(), entity->GetTransform() });
	}

	static Ref<Shader> equirectangularConversionShader, envFilteringShader, envIrradianceShader;

	// Shaders in this function are all compute shaders.
	std::pair<Ref<TextureCube>, Ref<TextureCube>> SceneRenderer::CreateEnvironmentMap(const std::string& filepath)
	{
		// 2K
		const uint32_t cubemapSize = 2048;
		const uint32_t irradianceMapSize = 32;
		
		// 将hdr文件加载为等距圆柱体投影
		Ref<Texture2D> envEquirect = Texture2D::Create(filepath);
		CPBR_CORE_ASSERT(envEquirect->GetFormat() == TextureFormat::Float16, "Texture is not HDR!");
		
		// 使用计算着色器将等距圆柱体投影转换为cubemap
		if (!equirectangularConversionShader)
			equirectangularConversionShader = Shader::Create("assets/shaders/EquirectangularToCubeMap.glsl");
		equirectangularConversionShader->Bind(); // glUseProgram()
		envEquirect->Bind(); // glBindTextureUnit();
		Ref<TextureCube> envUnfiltered = TextureCube::Create(TextureFormat::Float16, cubemapSize, cubemapSize);
		Renderer::Submit([envUnfiltered, cubemapSize, envEquirect]()
		{
			/*
			 * 计算着色器中的环境贴图
			 * 首先，glBindImageTexture()函数将一个纹理绑定到图像单元0上，该纹理是
			 * envUnfiltered对象的渲染器ID。然后，glDispatchCompute()函数根据cubemapSize的大小，将计算分派到多个计算单元中
			 * 进行计算。最后，glGenerateTextureMipmap()函数生成envUnfiltered纹理的mipmap。
			 */
			glBindImageTexture(0, envUnfiltered->GetRendererID(), 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA16F);
			glDispatchCompute(cubemapSize / 32, cubemapSize / 32, 6);
			glGenerateTextureMipmap(envUnfiltered->GetRendererID());		
		});

		// 使用计算着色器生成多级预过滤环境立方体贴图radiance
		if (!envFilteringShader)
			envFilteringShader = Shader::Create("assets/shaders/EnvironmentMipFilter.glsl");
		envFilteringShader->Bind();
		envUnfiltered->Bind();
		Ref<TextureCube> envFiltered = TextureCube::Create(TextureFormat::Float16, cubemapSize, cubemapSize);
		Renderer::Submit([envUnfiltered, envFiltered, cubemapSize]()
		{
			// 拷贝一份texture
			glCopyImageSubData(envUnfiltered->GetRendererID(), GL_TEXTURE_CUBE_MAP, 0, 0, 0, 0,
				envFiltered->GetRendererID(), GL_TEXTURE_CUBE_MAP, 0, 0, 0, 0,
				envFiltered->GetWidth(), envFiltered->GetHeight(), 6);
			/*
			 * 这段代码是用于对环境立方体贴图进行多级预过滤的。它使用了一个循环，从第二级开始，每次减小尺寸为原来的一半，
			 * 直到达到最后一级。在每个级别上，它绑定了envFiltered对象的渲染器ID到图像单元0上，并使用glBindImageTexture()
			 * 函数将其作为写入目标。然后，它通过调用glProgramUniform1f()函数将当前级别的粗糙度值传递给envFilteringShader
			 * 着色器程序的uniform变量。最后，它使用glDispatchCompute()函数将计算任务分派给多个计算单元进行计算，其中每个计算
			 * 单元的尺寸为numGroups * numGroups * 6。这样，通过循环和多级预过滤，可以逐渐降低环境立方体贴图的分辨率和粗糙度，
			 * 以提高渲染性能和效果。
			 */
			const float deltaRoughness = 1.0f / glm::max((float)(envFiltered->GetMipLevelCount() - 1.0f), 1.0f);
			for (int level = 1, size = cubemapSize / 2; level < envFiltered->GetMipLevelCount(); level++, size /= 2) // <= ?
			{
				const GLuint numGroups = glm::max(1, size / 32);
				glBindImageTexture(0, envFiltered->GetRendererID(), level, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA16F);
				glProgramUniform1f(envFilteringShader->GetRendererID(), 0, level * deltaRoughness);
				glDispatchCompute(numGroups, numGroups, 6);
			}
		});


		// 计算IBL的漫反射辐照度立方体贴图的卷积irradiance
		if (!envIrradianceShader)
			envIrradianceShader = Shader::Create("assets/shaders/EnvironmentIrradiance.glsl");
		envIrradianceShader->Bind();
		envFiltered->Bind();
		Ref<TextureCube> irradianceMap = TextureCube::Create(TextureFormat::Float16, irradianceMapSize, irradianceMapSize);
		Renderer::Submit([irradianceMap]()
		{
			glBindImageTexture(0, irradianceMap->GetRendererID(), 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA16F);
			glDispatchCompute(irradianceMap->GetWidth() / 32, irradianceMap->GetHeight() / 32, 6);
			glGenerateTextureMipmap(irradianceMap->GetRendererID());
		});

		return { envFiltered, irradianceMap };
	}

	void SceneRenderer::GeometryPass()
	{
		Renderer::BeginRenderPass(s_Data.GeoPass);

		auto viewProjection = s_Data.SceneData.SceneCamera.GetViewProjection();

		// Skybox
		auto skyboxShader = s_Data.SceneData.SkyboxMaterial->GetShader();
		s_Data.SceneData.SkyboxMaterial->Set("u_InverseVP", glm::inverse(viewProjection));
		// s_Data.SceneInfo.EnvironmentIrradianceMap->Bind(0);
		Renderer::SubmitFullscreenQuad(s_Data.SceneData.SkyboxMaterial);

		// Render entities
		for (auto& dc : s_Data.DrawList)
		{
			auto baseMaterial = dc.Mesh->GetMaterial();
			baseMaterial->Set("u_ViewProjectionMatrix", viewProjection);
			baseMaterial->Set("u_CameraPosition", s_Data.SceneData.SceneCamera.GetPosition());

			// Environment (TODO: don't do this per mesh)
			baseMaterial->Set("u_EnvRadianceTex", s_Data.SceneData.SceneEnvironment.RadianceMap);
			baseMaterial->Set("u_EnvIrradianceTex", s_Data.SceneData.SceneEnvironment.IrradianceMap);
			baseMaterial->Set("u_BRDFLUTTexture", s_Data.BRDFLUT);

			auto overrideMaterial = nullptr; // dc.Material;
			Renderer::SubmitMesh(dc.Mesh, dc.Transform, overrideMaterial);
		}

		// Grid
		if (GetOptions().ShowGrid)
		{
			s_Data.GridMaterial->Set("u_ViewProjection", viewProjection);
			Renderer::SubmitQuad(s_Data.GridMaterial, glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(16.0f)));
		}

		if (GetOptions().ShowBoundingBoxes)
		{
			Renderer2D::BeginScene(viewProjection);
			for (auto & dc : s_Data.DrawList)
			{
				Renderer::DrawAABB(dc.Mesh);
			}
			Renderer2D::EndScene();
		}
		
		Renderer::EndRenderPass();
	}

	void SceneRenderer::CompositePass()
	{
		Renderer::BeginRenderPass(s_Data.CompositePass);
		s_Data.CompositeShader->Bind();
		s_Data.CompositeShader->SetFloat("u_Exposure", s_Data.SceneData.SceneCamera.GetExposure());
		s_Data.CompositeShader->SetInt("u_TextureSamples", s_Data.GeoPass->GetSpecification().TargetFramebuffer->GetSpecification().Samples);
		s_Data.GeoPass->GetSpecification().TargetFramebuffer->BindTexture();
		Renderer::SubmitFullscreenQuad(nullptr);
		Renderer::EndRenderPass();
	}

	void SceneRenderer::FlushDrawList()
	{
		CPBR_CORE_ASSERT(!s_Data.ActiveScene, "");

		GeometryPass();
		CompositePass();

		s_Data.DrawList.clear();
		s_Data.SceneData = {};
	}

	Ref<RenderPass> SceneRenderer::GetFinalRenderPass()
	{
		return s_Data.CompositePass;
	}
	
	Ref<Texture2D> SceneRenderer::GetFinalColorBuffer()
	{
		// return s_Data.CompositePass->GetSpecification().TargetFramebuffer;
		CPBR_CORE_ASSERT(false, "Not implemented");
		return nullptr;
	}

	uint32_t SceneRenderer::GetFinalColorBufferRendererID()
	{
		return s_Data.CompositePass->GetSpecification().TargetFramebuffer->GetColorAttachmentRendererID();
	}

	SceneRendererOptions& SceneRenderer::GetOptions()
	{
		return s_Data.Options;
	}
}