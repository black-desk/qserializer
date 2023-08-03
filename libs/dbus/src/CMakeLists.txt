add_library (qserializer_dbus INTERFACE)

target_compile_features (
        qserializer_dbus INTERFACE
                                 cxx_std_17
)
target_sources (
        qserializer_dbus
        INTERFACE
                FILE_SET public_headers TYPE HEADERS BASE_DIRS
                ${PROJECT_SOURCE_DIR}/libs/dbus/include FILES
                ${PROJECT_SOURCE_DIR}/libs/dbus/include/qserializer/dbus.h
                ${PROJECT_SOURCE_DIR}/libs/dbus/include/qserializer/detail/dbus/operators.h
)

target_link_libraries (
        qserializer_dbus
        INTERFACE
                QSerializer::Core Qt::DBus
)

add_library (QSerializer::DBus ALIAS qserializer_dbus)

add_library (
        qserializer_dbus_CHECK
        ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/dbus.check.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/detail/dbus/operators.check.cpp
)

target_link_libraries (
        qserializer_dbus_CHECK
        PUBLIC
                QSerializer::DBus
)
