//
// Note:	this file is to be included in client applications ONLY
//			NEVER include this file anywhere in the engine codebase
//
#pragma once

#include "Capybara/Core/Application.h"
#include "Capybara/Core/Log.h"
#include "Capybara/Core/TimeStep.h"

#include "Capybara/Core/Events/Event.h"
#include "Capybara/Core/Events/ApplicationEvent.h"
#include "Capybara/Core/Events/KeyEvent.h"
#include "Capybara/Core/Events/MouseEvent.h"

#include "imgui/imgui.h"

// --- Capybara Render API ------------------------------
#include "Capybara/Renderer/Renderer.h"
#include "Capybara/Renderer/RenderPass.h"
#include "Capybara/Renderer/SceneRenderer.h"
#include "Capybara/Renderer/Framebuffer.h"
#include "Capybara/Renderer/Buffer.h"
#include "Capybara/Renderer/VertexArray.h"
#include "Capybara/Renderer/Texture.h"
#include "Capybara/Renderer/Shader.h"
#include "Capybara/Renderer/Mesh.h"
#include "Capybara/Renderer/Camera.h"
#include "Capybara/Renderer/Material.h"
// ---------------------------------------------------

#include "Capybara/Scene/Entity.h"
#include "Capybara/Scene/Scene.h"