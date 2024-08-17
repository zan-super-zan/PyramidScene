workspace "PyramidScene"
    architecture "x64"
    configurations { "Debug", "Release" }
    location "."

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "PyramidScene"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp", 
        "%{prj.name}/vendor/glm/**.hpp", 
        "%{prj.name}/vendor/glm/**.h", 
        "%{prj.name}/vendor/glad.c",
        "%{prj.name}/vendor/imgui/**.h",
        "%{prj.name}/vendor/imgui/**.cpp"
    }
    includedirs {
        "%{wks.location}/vendor/glfw/include",
        "%{wks.location}/vendor/glad/include",
        "%{prj.name}/vendor"
    }
    libdirs {
        "%{wks.location}/vendor/glfw/lib"
    }

    links {
        "opengl32.lib",
        "glfw3.lib"
    }
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        runtime "Release"
        symbols "Off"
        optimize "On"