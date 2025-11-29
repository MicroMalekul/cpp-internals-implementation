set(TARGET_NAME lru_cache)

add_executable(${TARGET_NAME} test.cpp ${TARGET_NAME}.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2WithMain)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})