project(test_PWRC)

add_executable(test_PWRC
        test_PWRC.cc)

target_include_directories(test_PWRC PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

target_link_directories(test_PWRC PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(test_PWRC PRIVATE controller)
