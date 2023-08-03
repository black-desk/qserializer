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
                FILE_SET private_headers TYPE HEADERS BASE_DIRS . FILES
                qserializer/tests/types/Base.h
                qserializer/tests/types/Page.h
                qserializer/tests/types/Book.h
)

target_link_libraries (
        qserializer_tests
        PRIVATE
                QSerializer::Core GTest::gtest_main
)

gtest_discover_tests (qserializer_tests)
