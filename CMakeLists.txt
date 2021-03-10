
# CMake project file.
# Set everything up before commencing with any builds.

cmake_minimum_required(VERSION 3.9)

project(890_2AssPlugin)

message(STATUS "Project:    ${PROJECT_NAME}")
message(STATUS "Platform:   ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM})")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

option(CB_ENABLE_TESTING "Enable unit testing." ON)
option(CB_ENABLE_LTO "Enable IPO/LTO builds." OFF)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## Work around bug in CMake where it doesn't add correct linker flags to generate
## Position Independent Code in linker step
## See: https://gitlab.kitware.com/cmake/cmake/issues/14983
## See: https://doc-kurento.readthedocs.io/en/stable/dev/hardening.html (does good job explaining)
if (CMAKE_POSITION_INDEPENDENT_CODE)

    set(ENABLE_PIE_WORKAROUND FALSE)

    if ("${CMAKE_MAJOR_VERSION}" LESS 3 OR ("${CMAKE_MAJOR_VERSION}" EQUAL 3 AND "${CMAKE_MINOR_VERSION}" LESS_EQUAL 13))
        message(STATUS "NOTE: Working around Position Indepdendent Code handling in CMake")

        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")
    endif()

endif()

if (CB_ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT supported OUTPUT error)

    if (supported )
        message(STATUS "IPO / LTO enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else ()
        message(FATAL "IPO / LTO not supported: <${error}>")
    endif()
endif()


if (MSVC)
    message(FATAL_ERROR "Windows is unsupported platform!")
elseif (CMAKE_COMPILER_IS_GNUCXX)

    # Options added:
    # 1. Increase warning level
    # 2. Make all warnings into errors.
    set(CB_CMAKE_CXX_TPSDK_FLAGS "${CB_CMAKE_CXX_TPSDK_FLAGS} -fstack-clash-protection -fstack-protector-strong")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

    # Pass -Wl,-z,defs. This makes sure all symbols are defined at compile-time. Otherwise a DSO
    # build might not work at runtime.
    set(CB_CMAKE_SHARED_LD_TPSDK_FLAGS "${CB_CMAKE_SHARED_LD_TPSDK_FLAGS} -Wl,--as-needed -Wl,-z,defs,-z,relro,-z,now")

elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    # Options added:
    # 1. Increase warning level
    # 2. Make all warnings into errors.
    set(CB_CMAKE_CXX_TPSDK_FLAGS "${CB_CMAKE_CXX_TPSDK_FLAGS} -fstack-protector-strong")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

    # Pass -Wl,-z,defs. This makes sure all symbols are defined at compile-time. Otherwise a DSO
    # build might not work at runtime.
    set(CB_CMAKE_SHARED_LD_TPSDK_FLAGS "${CB_CMAKE_SHARED_LD_TPSDK_FLAGS} -Wl,-z,defs,-z,relro,-z,now")

else ()
    message(FATAL_ERROR "Unsupported platform!")
endif ()

set(CB_CMAKE_C_TPSDK_FLAGS ${CB_CMAKE_C_TPSDK_FLAGS} ${CB_CMAKE_CXX_TPSDK_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CB_CMAKE_CXX_TPSDK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CB_CMAKE_SHARED_LD_TPSDK_FLAGS}")

# Set the location where our binaries will be stored.
# WARN/TODO: Not quite right, because .lib or .a files should
#            not go in the bin folder!
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

link_directories(${CMAKE_BINARY_DIR}/bin)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

################################################################
# GTest yamc.
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    #GIT_SHALLOW 1 # (ambiguous when using GIT_TAG)
    #GIT_PROGRESS 1
    GIT_TAG 703bd9caab50b139428cea1aaff9974ebee5742e # Release 1.10.0
    UPDATE_DISCONNECTED 1
    TIMEOUT 60
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=RELWITHDEBINFO -Dgtest_build_tests=OFF -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

ExternalProject_Get_Property(googletest binary_dir)
add_library(gtest UNKNOWN IMPORTED)
add_library(gtest_main UNKNOWN IMPORTED)
set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/libgtest.a
    )
set_target_properties(gtest_main PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
    )
add_dependencies(gtest googletest)
add_dependencies(gtest_main googletest)

################################################################
# Google Test - download and install GoogleTest
find_package(GTest REQUIRED)

# Adds 'd' onto artifacts - does NOT apply to executables.
# For executables, this needs to be done an exec-by-exec
# basis.
set(CMAKE_DEBUG_POSTFIX "d")

include_directories(include)

# Add the subdirectories we need to process. Can now
# get out of the starting blocks.
add_subdirectory(source)

if (CB_ENABLE_TESTING)
    # Enable unit testing. This will create a 'make test' target on Makefile generators.
    enable_testing()

    add_subdirectory(test)
endif ()
