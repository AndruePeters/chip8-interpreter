cmake_minimum_required(VERSION 3.8)
project(chip8 VERSION 0.0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"


# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_17)
target_include_directories(project_options INTERFACE include)

if (MSVC)
    target_compile_options(project_warnings INTERFACE /W4 /WX "/permissive-")
else ()

    target_compile_options(project_warnings
                            INTERFACE
                            -Wall
                            -Wextra # reasonable and standard
                            -Wshadow # warn the user if a variable declaration shadows one from a
                                    # parent context
                            -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                                                # non-virtual destructor. This helps catch hard to
                                                # track down memory errors
                            -Wold-style-cast # warn for c-style casts
                            -Wcast-align # warn for potential performance problem casts
                            -Wunused # warn on anything being unused
                            -Woverloaded-virtual # warn if you overload (not override) a virtual
                                                # function
                            -Wpedantic # warn if non-standard C++ is used
                            -Wconversion # warn on type conversions that may lose data
                            -Wsign-conversion # warn on sign conversions
                            -Wmisleading-indentation # warn if identation implies blocks where blocks
                                                    # do not exist
                            -Wduplicated-cond # warn if if / else chain has duplicated conditions
                            -Wduplicated-branches # warn if if / else branches have duplicated code
                            -Wlogical-op # warn about logical operations being used where bitwise were
                                        # probably wanted
                            -Wnull-dereference # warn if a null dereference is detected
                            -Wuseless-cast # warn if you perform a cast to the same type
                            -Wdouble-promotion # warn if float is implicit promoted to double
                            -Wformat=2 # warn on security issues around functions that format output
                                        # (ie printf)
                            )
endif()

#
# Load Conan
#
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file( DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check(REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP
                CONAN_COMMAND ${CONAN_CMD}
                BUILD missing)

find_package(fmt)
find_package(rang)
find_package(spdlog)

add_executable(chip8 src/main.cpp)
set_property(TARGET chip8 PROPERTY CXX_STANDARD 17)
target_link_libraries(chip8 PRIVATE project_options
                                    project_warnings
                                    fmt::fmt)