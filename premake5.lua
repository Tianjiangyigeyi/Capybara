workspace "Capybara"
architecture "x64"

configurations {"Debug", "Release", "Dist"}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Debug-Windows-x64

project "Capybara"
location "Capybara"
kind "SharedLib" -- dll
language "C++"

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

pchheader "precomp.h"
pchsource "Capybara/src/precomp.cpp"

files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}
includedirs {"%{prj.name}/src", "%{prj.name}/vendor/spdlog/include"}
filter "system:windows"
cppdialect "C++17"
staticruntime "On" -- linking the runtime library
systemversion "latest"

defines {"CPBR_BUILD_DLL", "CPBR_PLATFORM_WINDOWS"}

-- create a postbuild step to put the .dll where we want to be
postbuildcommands {("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")}

filter "configurations:Debug" -- only apply to Debug configurations
defines "CPBR_DEGUG"
symbols "On"

filter "configurations:Release" -- only apply to Debug configurations
defines "CPBR_RELEASE"
optimize "On"

filter "configurations:Dist" -- only apply to Debug configurations
defines "CPBR_DIST"
optimize "On"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp" -- .exe
language "C++"

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")
pchheader "precomp.h"
pchsource "Sandbox/src/precomp.cpp"
files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}
includedirs {"Capybara/vendor/spdlog/include", "Capybara/src"}

links {"Capybara"}

filter "system:windows"
cppdialect "C++17"
staticruntime "On" -- linking the runtime library
systemversion "latest"

defines {"CPBR_PLATFORM_WINDOWS"}

filter "configurations:Debug" -- only apply to Debug configurations
defines "CPBR_DEGUG"
symbols "On"

filter "configurations:Release" -- only apply to Debug configurations
defines "CPBR_RELEASE"
optimize "On"

filter "configurations:Dist" -- only apply to Debug configurations
defines "CPBR_DIST"
optimize "On"
