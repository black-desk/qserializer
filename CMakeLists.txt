cmake_minimum_required (
        VERSION
                3.13.4
)

project (
        qserializer
        LANGUAGES
                CXX
)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)

set (
        QT_VERSION_MAJOR
        "6"
        CACHE
                STRING "The qt major version tests and examples link to."
)

find_package (
        Qt${QT_VERSION_MAJOR}
        COMPONENTS
                Core DBus
        REQUIRED
)

add_library (qserializer INTERFACE)
add_library (qserializer::qserializer ALIAS qserializer)

target_sources (
        qserializer
        INTERFACE
                include/qserializer/qserializer.h
                include/qserializer/qserializer_dbus.h
)

target_link_libraries (
        qserializer
        INTERFACE
                Qt::Core Qt::DBus
)

target_include_directories (
        qserializer
        INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(PROJECT_IS_TOP_LEVEL)
        add_subdirectory (examples)

        include (CTest)
        include (GoogleTest)
        enable_testing ()
        find_package (GTest REQUIRED)
        add_subdirectory (tests)
endif()
