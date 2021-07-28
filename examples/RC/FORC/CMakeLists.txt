project(test_FORC)

add_executable(test_FORC
        test_FORC.cc)

target_include_directories(test_FORC PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

target_link_directories(test_FORC PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(test_FORC PRIVATE controller)
