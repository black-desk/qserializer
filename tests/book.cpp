#include "book.hpp"

#include "custom_converter.hpp"

Q_REGISTER_SERIALIZER(Book, { registerQListQStringConveter(); });
