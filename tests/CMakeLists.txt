add_executable(tests)
aux_source_directory(. example_SOURCE)
target_sources(
  tests
  PRIVATE ${example_SOURCE}
)
target_link_libraries(
  tests
  PRIVATE qserializer GTest::gtest_main
)

gtest_discover_tests(tests)
