cmake_minimum_required(VERSION 3.15)

project("qserializer")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_library(qserializer INTERFACE)
target_include_directories(qserializer INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(qserializer INTERFACE Qt6::Core)

add_subdirectory(examples/simple)
