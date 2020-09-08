add_executable(chip8 main.cpp)
target_link_libraries(chip8 PUBLIC
        project_options
        project_warnings
        cpulib
        CONAN_PKG::fmt
        CONAN_PKG::imgui-sfml
        )