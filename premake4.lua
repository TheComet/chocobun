-------------------------------------------------------------------
-- Chocobun build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then
	
	-- global header include directories
	headerSearchDirs = {
		"chocobun-core",
		"chocobun-console"
	}
	
	-- lib include directories
	libSearchDirs = {
		"bin/lib",
	}
	
	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core_d"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"chocobun-core",
		"chocobun-console",
		"usr/local/include/",
	}

	-- lib include directories
	libSearchDirs = {
		"bin/debug",
		"bin/release",
		"usr/local/lib",
		"usr/lib"
	}

	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core_d"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}
	
-- MAAAC
elseif os.get() == "macosx" then

	-- header search directories
	headerSearchDirs = {
		"chocobun-core",
		"chocobun-console",
		"usr/include/"
	}

	-- lib include directories
	libSearchDirs = {
		"bin/debug",
		"bin/release",
		"usr/local/lib",
		"usr/lib"
	}

	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core_d"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Chocobun Solution
-------------------------------------------------------------------

solution "Chocobun"
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
		"CHOCOBUN_CORE_DYNAMIC"
	}
	
	-------------------------------------------------------------------
	-- Chocobun core
	-------------------------------------------------------------------
	
	project "chocobun-core"
		kind "SharedLib"
		language "C++"
		files {
			"chocobun-core/**.cpp",
			"chocobun-core/**.hpp"
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
			links (linklibs_chocobun_core_debug)
			
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
			links (linklibs_chocobun_core_release)
			
	-------------------------------------------------------------------
	-- Chocobun console
	-------------------------------------------------------------------
	
	project "chocobun-console"
		kind "ConsoleApp"
		language "C++"
		files {
			"chocobun-console/**.cpp",
			"chocobun-console/**.hpp"
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
			links (linklibs_chocobun_console_debug)
			
		configuration "Release"
			targetdir "bin/relesae"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_chocobun_console_release)
