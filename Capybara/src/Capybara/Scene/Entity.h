#pragma once

#include <glm/glm.hpp>

#include "Capybara/Renderer/Mesh.h"

namespace Capybara {

	class Entity
	{
	public:
		~Entity();

		// TODO: Move to Component
		void SetMesh(const Ref<Mesh>& mesh) { m_Mesh = mesh; }
		Ref<Mesh> GetMesh() { return m_Mesh; }

		const std::string& GetName() const { return m_Name; }
		void SetMaterial(const Ref<MaterialInstance>& material) { m_Material = material; }
		Ref<MaterialInstance> GetMaterial() { return m_Material; }

		const glm::mat4& GetTransform() const { return m_Transform; }
		glm::mat4& Transform() { return m_Transform; }
	private:
		Entity(const std::string& name);
		glm::mat4 m_Transform;
		std::string m_Name;
		// TODO: Temp
		Ref<Mesh> m_Mesh;
		Ref<MaterialInstance> m_Material;

		friend class Scene;
	};

}