add_executable(example)
aux_source_directory(. example_SOURCE)
target_sources(example PRIVATE ${example_SOURCE})
target_link_libraries(example PRIVATE qserilizer)
