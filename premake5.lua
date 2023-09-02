workspace "Capybara"
    architecture "x64"
    startproject "Sandbox"
    configurations 
    {
        "Debug", 
        "Release", 
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Debug-Windows-x64

IncludeDir = {}
IncludeDir["GLFW"] = "Capybara/vendor/GLFW/include"
IncludeDir["Glad"] = "Capybara/vendor/Glad/include"
IncludeDir["ImGui"] = "Capybara/vendor/imgui"
IncludeDir["glm"] = "Capybara/vendor/glm"

include "Capybara/vendor/GLFW"
include "Capybara/vendor/Glad"
include "Capybara/vendor/imgui"



project "Capybara"
    location "Capybara"
    kind "StaticLib" -- lib
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "precomp.h"
    pchsource "Capybara/src/precomp.cpp"

    files 
    {
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
        
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs 
    {"%{prj.name}/src", 
     "%{prj.name}/vendor/spdlog/include", 
     "%{IncludeDir.GLFW}",
     "%{IncludeDir.Glad}",
     "%{IncludeDir.ImGui}",
     "%{IncludeDir.glm}"
    }

    links 
    {
        "GLFW", 
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
    systemversion "latest"

    defines 
    {
        "CPBR_BUILD_DLL", 
        "CPBR_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE"
    }

   
    filter "configurations:Debug" -- only apply to Debug configurations
    defines "CPBR_DEGUG"
    runtime "Debug"
    symbols "on"
    
    filter "configurations:Release" -- only apply to Debug configurations
    defines "CPBR_RELEASE"
    runtime "Release"
    optimize "on"

    filter "configurations:Dist" -- only apply to Debug configurations
    defines "CPBR_DIST"
    runtime "Release"
    optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp" -- .exe
    language "C++"
    cppdialect "C++17"
    staticruntime "on" 
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "precomp.h"
    --pchsource "Sandbox/src/precomp.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "Capybara/vendor/spdlog/include", 
        "Capybara/src",
        "Capybara/vendor",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }
    
    links 
    {
        "Capybara"
    }
    
    filter "system:windows"
    systemversion "latest"
    
    defines {"CPBR_PLATFORM_WINDOWS"}
    
    filter "configurations:Debug" -- only apply to Debug configurations
    defines "CPBR_DEGUG"
    runtime "Debug"
    symbols "on"
    
    filter "configurations:Release" -- only apply to Debug configurations
    defines "CPBR_RELEASE"
    runtime "Release"
    optimize "on"
    
    filter "configurations:Dist" -- only apply to Debug configurations
    defines "CPBR_DIST"
    runtime "Release"
    optimize "on"
