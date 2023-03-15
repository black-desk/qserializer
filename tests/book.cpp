#include "book.hpp"

#include "custom_converter.hpp"

QSERIALIZER_INIT_IMPL(Book, { registerQListQStringConveter(); });
