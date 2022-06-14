workspace "oxy"
	architecture "x64"
	startproject "Window-Test"
	targetdir "build"
	warnings "Off"

	configurations { "Debug","Release" }
	
	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Get Vulkan SDK location from the environment variable
VulkanSDK = os.getenv("VULKAN_SDK")
VulkanLibs = "%{VulkanSDK}/Lib" 

group "Core"
project "oxy"
	location "oxy"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src/" }

	links {}

	filter "system:not windows"
		systemversion "latest"
		cppdialect "C++2a"
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"

		links { "dwmapi", "opengl32.lib", "%{VulkanLibs}/vulkan-1.lib" }

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			symbols "On"
			runtime "Release"
			optimize "On"
	
	filter "system:linux"
		systemversion "latest"
		cppdialect "C++2a"

		links { "GL", "X11", "%{VulkanLibs}/vulkan-1.so" }

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			symbols "On"
			runtime "Release"
			optimize "On"

-- Examples
group "Examples"
project "Window-Test"
	location "Examples/Window-Test"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src/", "oxy/src" }

	links { "oxy" }

	filter "system:not windows"
		systemversion "latest"
		cppdialect "C++2a"

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"

		links { "dwmapi", "opengl32.lib", "%{VulkanLibs}/vulkan-1.lib" }

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			symbols "On"
			runtime "Release"
			optimize "On"

	filter "system:linux"
		systemversion "latest"
		cppdialect "C++2a"

		links { "GL", "X11", "%{VulkanLibs}/vulkan-1.so" }

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			symbols "On"
			runtime "Release"
			optimize "On"
