-- premake5.lua
workspace "ACREngine" -- name of the solution
   
   architecture "x86" -- can be x64, although fullscreen is buggy that way
   startproject "Application"
   location "../"

   configurations { "Debug", "Release" } -- configurations of the solution
   
   -- specifications when using Debug configuration
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
   
   -- specifications when using Release configuration
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"


project "Application" -- name of the project
   kind "WindowedApp" -- despite running in the console, we want to create the console at runtime.
   language "C"
   location "../application"

   vpaths {
      ["Header Files"] = { "../application/**.h", "../application/**.hpp"},
      ["ACRE Files"] = { "../acre files/**.h", "../acre files/**.hpp" },
      ["Source Files"] = {"../application/**.c", "../application/**.cpp"}
   }
  
   files { "../application/**.c", "../application/**.h", "../application/**.hpp", "../application/**.cpp", "../acre files/**.h", "../acre files/**.hpp" }
   targetdir "../build/%{cfg.buildcfg}"