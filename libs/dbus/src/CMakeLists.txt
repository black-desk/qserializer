add_library (qserializer_dbus INTERFACE)

target_compile_features (
        qserializer_dbus INTERFACE
                                 cxx_std_17
)
target_sources (
        qserializer_dbus
        INTERFACE
                FILE_SET public_headers TYPE HEADERS BASE_DIRS ../include FILES
                ../include/qserializer/dbus.h
                ../include/qserializer/detail/dbus/operators.h
)

target_link_libraries (
        qserializer_dbus
        INTERFACE
                QSerializer::Core Qt::DBus
)

add_library (QSerializer::DBus ALIAS qserializer_dbus)

add_library (
        qserializer_dbus_check EXCLUDE_FROM_ALL
        qserializer/dbus.cpp qserializer/detail/dbus/operators.cpp
)

target_link_libraries (
        qserializer_dbus_check
        PUBLIC
                QSerializer::DBus
)
