enable_testing()
add_executable(memTest memory_unit_test.cpp)
target_link_libraries(memTest
                      PRIVATE project_options 
                      project_warnings
                      cpulib
                      CONAN_PKG::gtest)
add_test(   NAME mem_test 
            COMMAND memTest )


add_executable(regTest register_unit_test.cpp)
target_link_libraries(regTest
                    PRIVATE project_options
                    cpulib
                    project_warnings
        CONAN_PKG::gtest )
add_test( NAME reg_test
        COMMAND regTest )


add_executable(stackTest stack_unit_test.cpp)
target_link_libraries(stackTest
                    PRIVATE project_options
                    cpulib
                    project_warnings
        CONAN_PKG::gtest)
add_test( NAME stack_test 
        COMMAND stackTest )

