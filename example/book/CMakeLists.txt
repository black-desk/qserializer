add_library(book include/book.h include/page.h include/base.h book.cpp page.cpp base.cpp)
target_link_libraries(book PUBLIC qserializer)
target_include_directories(book PUBLIC include)
