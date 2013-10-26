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
		"chocobun-core/include",
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
	linklibs_chocobun_tests_debug = {
		"chocobun-core_d",
		"gmock"
	}
	linklibs_chocobun_tests_release = {
		"chocobun-core",
		"gmock"
	}
	
-- MAAAC
elseif os.get() == "macosx" then

	-- header search directories
	headerSearchDirs = {
		"chocobun-core/include",
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
			"chocobun-core/**.hpp",
			"chocobun-core/**.hxx"
		}
		
		includedirs (headerSearchDirs)
		
		configuration "Debug"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/debug"
			else
				targetdir "bin/debug"
			end
			targetsuffix "_d"
			if os.get() == "windows" then
				implibdir "bin/lib"
			end
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
			if os.get() == "windows" then
				implibdir "bin/lib"
			end
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
			targetdir "bin/release"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_chocobun_console_release)

	-------------------------------------------------------------------
	-- Unit tests
	-------------------------------------------------------------------

	project "chocobun-tests"
		kind "ConsoleApp"
		language "C++"
		files {
			"chocobun-tests/**.cpp",
			"chocobun-tests/**.hpp"
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
			links (linklibs_chocobun_tests_debug)
			linkoptions {
				"-pthread" -- google mock 1.5.0 and greater use threads
			}

		configuration "Release"
			targetdir "bin/release"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_chocobun_tests_release)
			linkoptions {
				"-pthread" -- google mock 1.5.0 and greater use threads
			}
