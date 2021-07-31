project(test_RC)

add_executable(test_RC
        test_RC.cc)

target_include_directories(test_RC PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

target_link_directories(test_RC PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(test_RC PRIVATE controller)
