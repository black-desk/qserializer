add_library (qserializer_core INTERFACE)

target_compile_features (
        qserializer_core INTERFACE
                                 cxx_std_17
)
target_sources (
        qserializer_core
        INTERFACE
                FILE_SET public_headers TYPE HEADERS BASE_DIRS
                ${PROJECT_SOURCE_DIR}/libs/core/include FILES
                ${PROJECT_SOURCE_DIR}/libs/core/include/qserializer/core.h
                ${PROJECT_SOURCE_DIR}/libs/core/include/qserializer/detail/QSerializer.h
)

target_link_libraries (
        qserializer_core
        INTERFACE
                Qt::Core
)

add_library (QSerializer::Core ALIAS qserializer_core)

add_library (
        qserializer_core_CHECK
        ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/core.check.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/detail/QSerializer.check.cpp
)

target_link_libraries (
        qserializer_core_CHECK
        PUBLIC
                QSerializer::Core
)
