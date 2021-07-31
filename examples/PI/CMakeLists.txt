project(test_PI)

add_executable(test_PI
        test_PI.cc)

target_include_directories(test_PI PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_directories(test_PI PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(test_PI PRIVATE controller)
