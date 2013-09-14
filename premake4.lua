-------------------------------------------------------------------
-- Sokoban build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then

	-- root directories of required libraries
	local rootDir_SFML = "$(SFML_HOME)"
	
	-- global header include directories
	headerSearchDirs = {
		"sokoban-core",
		"sokoban-console",
		"sokoban-sfml"
	}
	
	-- lib include directories
	libSearchDirs = {
		"bin/lib",
		
		rootDir_SFML .. "/lib"
	}
	
	-- link libraries
	linklibs_sokoban_core_debug = { ""
	}
	linklibs_sokoban_core_release = { ""
	}
	linklibs_sokoban_console_debug = {
		"sokoban-core_d"
	}
	linklibs_sokoban_console_release = {
		"sokoban-core"
	}
	linklibs_sokoban_sfml_debug = {
	}
	linklibs_sokoban_sfml_release = {
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"sokoban-core",
		"sokoban-console",
		"sokoban-sfml",
		"usr/local/include/",
		"usr/local/include/SFML"
	}

	-- lib include directories
	libSearchDirs = {
		"bin/debug",
		"bin/release",
		"usr/local/lib",
		"usr/lib"
	}

	-- link libraries
	linklibs_sokoban_core_debug = {
	}
	linklibs_sokoban_core_release = {
	}
	linklibs_sokoban_console_debug = {
		"sokoban-core_d"
	}
	linklibs_sokoban_console_release = {
		"sokoban-core"
	}
	linklibs_sokoban_sfml_debug = {
	}
	linklibs_sokoban_sfml_release = {
	}

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Sokoban Solution
-------------------------------------------------------------------

solution "Sokoban"
	configurations { "Debug", "Release" }
	location "build"
	
	-------------------------------------------------------------------
	-- Global #defines
	-------------------------------------------------------------------
	
	-- Windows specific
	if os.get() == "Windows" then
		defines {
			"WIN32",
			"_WINDOWS"
		}
	end
	
	-- Project #defines
	defines {
		"SOKOBAN_CORE_DYNAMIC"
	}
	
	-------------------------------------------------------------------
	-- Sokoban core
	-------------------------------------------------------------------
	
	project "sokoban-core"
		kind "SharedLib"
		language "C++"
		files {
			"sokoban-core/**.cpp",
			"sokoban-core/**.hpp"
		}
		
		includedirs (headerSearchDirs)
		
		configuration "Debug"
			targetdir "bin/debug"
			targetsuffix "_d"
			implibdir "bin/lib"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_sokoban_core_debug)
			
		configuration "Release"
			targetdir "bin/release"
			implibdir "bin/lib"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_sokoban_core_release)
			
	-------------------------------------------------------------------
	-- Sokoban console
	-------------------------------------------------------------------
	
	project "sokoban-console"
		kind "ConsoleApp"
		language "C++"
		files {
			"sokoban-console/**.cpp",
			"sokoban-console/**.hpp"
		}
		
		includedirs (headerSearchDirs)
		
		configuration "Debug"
			targetdir "bin/debug"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_sokoban_console_debug)
			
		configuration "Release"
			targetdir "bin/relesae"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_sokoban_console_release)
