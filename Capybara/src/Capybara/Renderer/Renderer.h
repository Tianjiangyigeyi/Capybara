#pragma once

#include "RenderCommandQueue.h"
#include "RenderPass.h"

#include "Mesh.h"

namespace Capybara {

	class ShaderLibrary;

	// TODO: Maybe this should be renamed to RendererAPI? Because we want an actual renderer vs API calls...
	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		// Commands
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(uint32_t count, PrimitiveType type, bool depthTest = true);
		
		// For OpenGL
		static void SetLineThickness(float thickness);

		static void ClearMagenta();

		static void Init();

		static const Scope<ShaderLibrary>& GetShaderLibrary();

		/*
		 * 各种与渲染有关的函数func都可以通过该函数发送给渲染队列去执行, 这些函数的类型可以是不同的, 但一般都是返回void, 因为非
		 * void的返回值浪费了
		 * 通过一个lambda函数赋值给一个指针, 将这个指针renderCmd传给RenderCommandQueue, 并且传入func的size, 这是因为在
		 * RenderCommandQueue的Allocate的实现里需要提前分配好这块函数的内存, 方便渲染队列执行这些函数的时候能用到(每一次tick
		 * 都会调用Render::WaitAndRender将当前渲染队列里的所有函数执行掉, 这是通过RenderCommandQueue里面的计数器实现的)
		 */
		template<typename FuncT>
		static void Submit(FuncT&& func)
		{
			// renderCmd是一个指针
			auto renderCmd = [](void* ptr) {
				auto pFunc = (FuncT*)ptr;
				(*pFunc)();

				// NOTE: Instead of destroying we could try and enforce all items to be trivally destructible
				// however some items like uniforms which contain std::strings still exist for now
				// static_assert(std::is_trivially_destructible_v<FuncT>, "FuncT must be trivially destructible");
				pFunc->~FuncT();
			};
			auto storageBuffer = GetRenderCommandQueue()->Allocate(renderCmd, sizeof(func));
			new (storageBuffer) FuncT(std::forward<FuncT>(func));
		}

		/*static void* Submit(RenderCommandFn fn, unsigned int size)
		{
			return s_Instance->m_CommandQueue.Allocate(fn, size);
		}*/

		static void WaitAndRender();

		// ~Actual~ Renderer here... TODO: remove confusion later
		static void BeginRenderPass(const Ref<RenderPass>& renderPass, bool clear = true);
		static void EndRenderPass();

		static void SubmitQuad(const Ref<MaterialInstance>& material, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitFullscreenQuad(const Ref<MaterialInstance>& material);
		static void SubmitMesh(const Ref<Mesh>& mesh, const glm::mat4& transform, const Ref<MaterialInstance>& overrideMaterial = nullptr);

		static void DrawAABB(const Ref<Mesh>& mesh, const glm::vec4& color = glm::vec4(1.0f));
	private:
		static Scope<RenderCommandQueue>& GetRenderCommandQueue();
	};

}
