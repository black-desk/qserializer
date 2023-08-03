#pragma once

#include "qserializer/detail/QSerializer.h"

#if QT_VERSION <= QT_VERSION_CHECK(6, 2, 0)
#define QSERIALIZER_DECLARE_SHAREDPOINTER_METATYPE(x) \
        Q_DECLARE_METATYPE(QSharedPointer<x>);
#else
#define QSERIALIZER_DECLARE_SHAREDPOINTER_METATYPE(x)
#endif

#define QSERIALIZER_DECLARE(T)                         \
        QSERIALIZER_DECLARE_SHAREDPOINTER_METATYPE(T); \
        namespace QSerializerPrivateNamespace##T       \
        {                                              \
                char init();                           \
                static char _ = init();                \
        };

#define QSERIALIZER_IMPL(T, ...)                                  \
        namespace QSerializerPrivateNamespace##T                  \
        {                                                         \
                char init()                                       \
                {                                                 \
                        static char _ = []() -> char {            \
                                qserializer::detail::QSerializer< \
                                        T>::registerConverters(); \
                                __VA_ARGS__;                      \
                                return 0;                         \
                        }();                                      \
                        return _;                                 \
                }                                                 \
        }
