project(test_PR)

add_executable(test_PR
        test_PR.cc)

target_include_directories(test_PR PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_directories(test_PR PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(test_PR PRIVATE controller)
