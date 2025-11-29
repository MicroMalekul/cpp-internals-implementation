set(TARGET_NAME itertools)

add_executable(${TARGET_NAME} test.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2WithMain)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})