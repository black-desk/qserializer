add_executable (tests)
target_sources (
        tests
        PRIVATE
                base.h base.cpp book.h book.cpp page.h page.cpp tests.cpp
                custom_converter.h custom_converter.cpp
)
target_link_libraries (
        tests
        PRIVATE
                qserializer::qserializer GTest::gtest_main
)

gtest_discover_tests (tests)
