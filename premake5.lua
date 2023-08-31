workspace "Capybara"
    architecture "x64"

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

include "Capybara/vendor/GLFW"
include "Capybara/vendor/Glad"


project "Capybara"
    location "Capybara"
    kind "SharedLib" -- dll
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "precomp.h"
    pchsource "Capybara/src/precomp.cpp"

    files 
    {
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {"%{prj.name}/src", 
     "%{prj.name}/vendor/spdlog/include", 
     "%{IncludeDir.GLFW}",
     "%{IncludeDir.Glad}"
    }

    links 
    {
        "GLFW", 
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
    cppdialect "C++17"
    staticruntime "On" -- linking the runtime library
    systemversion "latest"

    defines 
    {
        "CPBR_BUILD_DLL", 
        "CPBR_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE"
    }

    -- create a postbuild step to put the .dll where we want to be
    postbuildcommands 
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    }

    filter "configurations:Debug" -- only apply to Debug configurations
    defines "CPBR_DEGUG"
    buildoptions "/MDd"
    symbols "On"
    
    filter "configurations:Release" -- only apply to Debug configurations
    defines "CPBR_RELEASE"
    buildoptions "/MD"
    optimize "On"

    filter "configurations:Dist" -- only apply to Debug configurations
    defines "CPBR_DIST"
    buildoptions "/MD"
    optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp" -- .exe
    language "C++"
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "precomp.h"
    pchsource "Sandbox/src/precomp.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "Capybara/vendor/spdlog/include", 
        "Capybara/src"
    }
    
    links 
    {
        "Capybara"
    }
    
    filter "system:windows"
    cppdialect "C++17"
    staticruntime "On" -- linking the runtime library
    systemversion "latest"
    
    defines {"CPBR_PLATFORM_WINDOWS"}
    
    filter "configurations:Debug" -- only apply to Debug configurations
    defines "CPBR_DEGUG"
    buildoptions "/MDd"
    symbols "On"
    
    filter "configurations:Release" -- only apply to Debug configurations
    defines "CPBR_RELEASE"
    buildoptions "/MD"
    optimize "On"
    
    filter "configurations:Dist" -- only apply to Debug configurations
    defines "CPBR_DIST"
    buildoptions "/MD"
    optimize "On"
