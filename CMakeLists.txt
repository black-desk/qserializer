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
        QSERIALIZER_QT_VERSION_MAJOR
        "6"
        CACHE
                STRING "The qt major version tests and examples link to."
)

find_package (
        Qt${QSERIALIZER_QT_VERSION_MAJOR}
        COMPONENTS
                Core DBus
        REQUIRED
)

add_library (QSerializerCore INTERFACE)
add_library (QSerializer::Core ALIAS QSerializerCore)

# cmake-format: off
target_sources (
        QSerializerCore
        PUBLIC
                FILE_SET HEADERS
                BASE_DIRS include
                FILES
                        include/QSerializer/QSerializer.h
)
# cmake-format: on

target_link_libraries (
        QSerializerCore
        INTERFACE
                Qt::Core
)

add_library (QSerializerDBus INTERFACE)
add_library (QSerializer::DBus ALIAS QSerializerDBus)

# cmake-format: off
target_sources (
        QSerializerDBus
        PUBLIC
                FILE_SET HEADERS
                BASE_DIRS include
                FILES
                        include/QSerializer/QSerializerDBus.h
)
# cmake-format: on

target_link_libraries (
        QSerializerDBus
        INTERFACE
                QSerializer::Core Qt::DBus
)

# Install

include (GNUInstallDirs)

# cmake-format: off
install (
        TARGETS QSerializerCore
        EXPORT QSerializerCore
        FILE_SET HEADERS
)

install (
        EXPORT QSerializerCore
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QSerializer
        FILE QSerializerCore.cmake
        NAMESPACE QSerializer::
        COMPONENT Core
)

install (
        TARGETS QSerializerDBus
        EXPORT QSerializerDBus
        FILE_SET HEADERS
)

install (
        EXPORT QSerializerDBus
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QSerializer
        FILE QSerializerDBus.cmake
        NAMESPACE QSerializer::
        COMPONENT DBus
)
# cmake-format: on

include (CMakePackageConfigHelpers)
set (cmakeModulesDir cmake)

# cmake-format: off
configure_package_config_file(
        misc/cmake/QSerializerConfig.cmake.in
        misc/cmake/QSerializerConfig.cmake
        INSTALL_DESTINATION
                ${CMAKE_INSTALL_LIBDIR}/cmake/QSerializer
        PATH_VARS
                cmakeModulesDir
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# cmake-format: on

# cmake-format: off
install (
        FILES
                ${CMAKE_CURRENT_BINARY_DIR}/misc/cmake/QSerializerConfig.cmake
        DESTINATION
                ${CMAKE_INSTALL_LIBDIR}/cmake/QSerializer
)
# cmake-format: on

if(NOT PROJECT_IS_TOP_LEVEL)
        return ()
endif()

# Build tests

option (
        QSERIALIZER_ENABLE_TESTING "QSerializer: build tests."
        ${PROJECT_IS_TOP_LEVEL}
)
if(QSERIALIZER_ENABLE_TESTING)
        include (CTest)
        include (GoogleTest)
        enable_testing ()
        find_package (GTest REQUIRED)
        add_subdirectory (tests)
endif()

# Build examples

add_subdirectory (examples)
