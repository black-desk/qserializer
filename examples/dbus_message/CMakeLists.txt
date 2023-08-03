if(NOT QSERIALIZER_ENABLE_DBUS)
        return ()
endif()

add_subdirectory (src)
add_subdirectory (apps)
