#include "book.hpp"

#include "custom_converter.hpp"      // for registerQListQStringConveter
#include "qserializer/qserializer.h" // for QSERIALIZER_IMPL

QSERIALIZER_IMPL(Book, { registerQListQStringConveter(); });
