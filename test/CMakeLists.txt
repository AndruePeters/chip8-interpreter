enable_testing()
add_executable(memTest memory_unit_test.cpp)
target_link_libraries(memTest
                      PRIVATE project_options 
                      project_warnings 
                      GTest::GTest GTest::Main)
add_test( NAME mem_test 
          COMMAND memTest )

