if(NOT QSERIALIZER_ENABLE_DBUS)
        return ()
endif()

add_subdirectory (src)

if(NOT QSERIALIZER_ENABLE_INSTALL)
        return ()
endif()

include (GNUInstallDirs)

# cmake-format: off
set_target_properties (
        qserializer_dbus
        PROPERTIES
                OUTPUT_NAME qserializer_dbus
                EXPORT_NAME DBus
)
# cmake-format: on

install (
        TARGETS
                qserializer_dbus
        EXPORT
                qserializer_dbus
        FILE_SET public_headers
)

install (
        EXPORT
                qserializer_dbus
        DESTINATION
                ${CMAKE_INSTALL_LIBDIR}/cmake/QSerializer
        FILE DBus.cmake
        NAMESPACE
                QSerializer::
)
