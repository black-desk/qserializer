add_library (qserializer_core INTERFACE)

target_compile_features (
        qserializer_core INTERFACE
                                 cxx_std_17
)
target_sources (
        qserializer_core
        INTERFACE
                FILE_SET public_headers TYPE HEADERS BASE_DIRS ../include FILES
                ../include/qserializer/Core.h
                ../include/qserializer/detail/QSerializer.h
)

target_link_libraries (
        qserializer_core
        INTERFACE
                Qt::Core
)

add_library (QSerializer::Core ALIAS qserializer_core)

add_library (
        qserializer_core_check EXCLUDE_FROM_ALL qserializer/Core.cpp
                                           qserializer/detail/QSerializer.cpp
)

target_link_libraries (
        qserializer_core_check
        PUBLIC
                QSerializer::Core
)
