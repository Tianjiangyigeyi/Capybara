workspace "Capybara"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
        "Release",
        "Dist"
    }

	startproject "CapybaraEditor"
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Capybara/vendor/GLFW/include"
IncludeDir["Glad"] = "Capybara/vendor/GLAD/include"
IncludeDir["ImGui"] = "Capybara/vendor/imgui"
IncludeDir["glm"] = "Capybara/vendor/glm"

include "Capybara/vendor/GLFW"
include "Capybara/vendor/GLAD"
include "Capybara/vendor/imgui"

project "Capybara"
    location "Capybara"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "precomp.h"
    pchsource "Capybara/src/precomp.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
    }

    includedirs
	{
		"%{prj.name}/src",
        "%{prj.name}/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{prj.name}/vendor/assimp/include",
        "%{prj.name}/vendor/assimp/include/assimp",
        "%{prj.name}/vendor/stb/include"
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
            "CPBR_PLATFORM_WINDOWS",
            "CPBR_BUILD_DLL"
		}

    filter "configurations:Debug"
        defines "CPBR_DEBUG"
        symbols "On"
                
    filter "configurations:Release"
        defines "CPBR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CPBR_DIST"
        optimize "On"

project "CapybaraEditor"
    location "CapybaraEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
        "Capybara"
    }
    
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}
    
	includedirs 
	{
        "%{prj.name}/src",
        "Capybara/src",
        "Capybara/vendor",
        "%{IncludeDir.glm}"
    }
	
	filter "system:windows"
        systemversion "latest"
                
		defines 
		{ 
            "CPBR_PLATFORM_WINDOWS"
		}
    
    filter "configurations:Debug"
        defines "CPBR_DEBUG"
        symbols "on"

		links
		{
			"Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
		}
                
    filter "configurations:Release"
        defines "CPBR_RELEASE"
        optimize "on"

		links
		{
			"Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
		}

    filter "configurations:Dist"
        defines "CPBR_DIST"
        optimize "on"

		links
		{
			"Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
        }
        
        project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
        links 
        { 
            "Capybara"
        }
        
        files 
        { 
            "%{prj.name}/src/**.h", 
            "%{prj.name}/src/**.c", 
            "%{prj.name}/src/**.hpp", 
            "%{prj.name}/src/**.cpp" 
        }
        
        includedirs 
        {
            "%{prj.name}/src",
            "Capybara/src",
            "Capybara/vendor",
            "%{IncludeDir.glm}"
        }
        
        filter "system:windows"
            systemversion "latest"
                    
            defines 
            { 
                "CPBR_PLATFORM_WINDOWS"
            }
        
        filter "configurations:Debug"
            defines "CPBR_DEBUG"
            symbols "on"
    
            links
            {
                "Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
            }
                    
        filter "configurations:Release"
            defines "CPBR_RELEASE"
            optimize "on"
    
            links
            {
                "Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
            }
    
        filter "configurations:Dist"
            defines "CPBR_DIST"
            optimize "on"
    
            links
            {
                "Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib"
            }