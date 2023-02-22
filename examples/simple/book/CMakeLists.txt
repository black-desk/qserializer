add_library(book include/book.h include/page.h book.cpp page.cpp)
target_link_libraries(book PUBLIC qserializer)
target_include_directories(book PUBLIC include)
