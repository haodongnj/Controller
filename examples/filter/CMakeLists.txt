project(test_filter)

add_executable(test_filter
        test_filter.c)

target_include_directories(test_filter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_directories(test_filter PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../..)
target_link_libraries(test_filter controller)
