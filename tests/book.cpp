#include "book.h"

#include <QtGlobal>                  // for QT_VERSION, QT_VERSION_CHECK
#include <qserializer/qserializer.h> // for QSERIALIZER_IMPL

#if QT_VERSION <= QT_VERSION_CHECK(6, 2, 0)
#include "custom_converter.h" // for registerQListQStringConveter
#endif

QSERIALIZER_IMPL(Book

#if QT_VERSION <= QT_VERSION_CHECK(6, 2, 0)
                 ,
                 { registerQListQStringConveter(); }
#endif

);
