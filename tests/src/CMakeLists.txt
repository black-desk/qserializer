add_library (qserializer_tests_CHECK qserializer/tests/utils.check.cpp)

target_sources (
        qserializer_tests_CHECK
        PRIVATE
                FILE_SET private_headers TYPE HEADERS BASE_DIRS
                ${CMAKE_CURRENT_SOURCE_DIR} FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/tests/utils.h
)

target_link_libraries (
        qserializer_tests_CHECK
        PRIVATE
                Qt::Core GTest::gtest_main
)

add_executable (
        qserializer_tests
        qserializer/tests/types/Base.cpp
        qserializer/tests/types/Page.cpp
        qserializer/tests/types/Book.cpp
        qserializer/tests/basics.cpp
)

target_sources (
        qserializer_tests
        PRIVATE
                FILE_SET private_headers TYPE HEADERS BASE_DIRS
                ${CMAKE_CURRENT_SOURCE_DIR} FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/tests/types/Base.h
                ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/tests/types/Page.h
                ${CMAKE_CURRENT_SOURCE_DIR}/qserializer/tests/types/Book.h
)

target_link_libraries (
        qserializer_tests
        PRIVATE
                QSerializer::Core GTest::gtest_main
)

gtest_discover_tests (qserializer_tests)
