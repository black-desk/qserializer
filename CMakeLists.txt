cmake_minimum_required(VERSION 3.13.4)

project(qserilizer LANGUAGES CXX)

# for private headers
include_directories(${CMAKE_SOURCE_DIR}/include)
# for generate private headers
include_directories(${CMAKE_BINARY_DIR}/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(qserilizer INTERFACE)
target_sources(qserilizer PUBLIC ./include/QSerializer ./include/qserializer.h)
target_link_libraries(qserilizer INTERFACE Qt5::Core)

include(CTest)
if(BUILD_TESTING)
        enable_testing()
        find_package(GTest REQUIRED)
        include(GoogleTest)
        add_subdirectory(tests)
endif()
