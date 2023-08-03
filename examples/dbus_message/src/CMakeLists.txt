add_library (
        qserializer_examples_dbusmessage
        qserializer/examples/dbus_message/Response.cpp
)

target_sources (
        qserializer_examples_dbusmessage
        PUBLIC
                FILE_SET public_headers TYPE HEADERS BASE_DIRS ../include FILES
                ../include/qserializer/examples/dbus_message/Response.h
)

target_link_libraries (
        qserializer_examples_dbusmessage
        PUBLIC
                QSerializer::DBus
)
