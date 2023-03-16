#include "book.hpp"

#include "custom_converter.hpp"

QSERIALIZER_IMPL(Book, { registerQListQStringConveter(); });
