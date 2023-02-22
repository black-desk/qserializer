add_subdirectory(book)

add_executable(simple main.cpp)
target_link_libraries(simple PRIVATE book)

target_include_directories(simple PRIVATE ${CMAKE_SOURCE_DIR}/include)
