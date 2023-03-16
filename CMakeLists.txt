cmake_minimum_required(VERSION 3.13.4)

project(qserializer LANGUAGES CXX)

# for private headers
include_directories(${CMAKE_SOURCE_DIR}/include)
# for generate private headers
include_directories(${CMAKE_BINARY_DIR}/include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core DBus)

add_library(qserializer INTERFACE)
target_sources(
  qserializer
  PUBLIC include/qserializer/qserializer.h include/qserializer/qserializer_dbus.h
)
target_link_libraries(
  qserializer
  INTERFACE Qt5::Core Qt5::DBus
)
target_include_directories(
  qserializer
  INTERFACE .
)

add_subdirectory(examples)

include(CTest)
if(BUILD_TESTING)
  include(GoogleTest)
  enable_testing()
  find_package(GTest REQUIRED)
  add_subdirectory(tests)
endif()
