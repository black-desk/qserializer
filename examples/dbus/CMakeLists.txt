qt5_generate_dbus_interface(server.h OPTIONS -A)

qt5_add_dbus_adaptor(adaptor_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/server.xml server.h Server)

add_executable(server ${adaptor_SOURCE} server.cpp response.cpp)
target_include_directories(
  server
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(
  server
  PRIVATE qserializer Qt5::Core Qt5::DBus
)

set_source_files_properties(
  ${CMAKE_CURRENT_BINARY_DIR}/server.xml PROPERTIES CLASSNAME ServerDBusI INCLUDE response.h
)
qt5_add_dbus_interface(interface_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/server.xml server_interface)

add_executable(client ${interface_SOURCE} client.cpp response.cpp)
target_include_directories(
  client
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(
  client
  PRIVATE qserializer Qt5::Core Qt5::DBus
)
