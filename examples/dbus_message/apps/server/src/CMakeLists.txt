set (
        spec
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../api/dbus/io.github.black_desk.TestDBusServer.xml
)

set (DBUS_SOURCES)

qt_add_dbus_adaptor (
        DBUS_SOURCES
        ${spec}
        qserializer/examples/dbus_message/Server.h
        qserializer::examples::dbus_message::Server
        qserializer/examples/dbus_message/gen_TestDBusServerAdaptor
        qserializer_examples_dbus_message_TestDBusServerAdaptor
)

add_executable (
        qserializer_examples_dbusmessage_server
        main.cpp qserializer/examples/dbus_message/Server.cpp ${DBUS_SOURCES}
)

target_sources (
        qserializer_examples_dbusmessage_server
        PUBLIC
                FILE_SET private_header TYPE HEADERS BASE_DIRS .
                ${CMAKE_CURRENT_BINARY_DIR} FILES
                qserializer/examples/dbus_message/Server.h
                qserializer/examples/dbus_message/TestDBusServerAdaptor.h
                ${CMAKE_CURRENT_BINARY_DIR}/qserializer/examples/dbus_message/gen_TestDBusServerAdaptor.h
)

target_link_libraries (
        qserializer_examples_dbusmessage_server
        PRIVATE
                qserializer_examples_dbusmessage
)
