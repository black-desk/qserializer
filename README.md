# QSerializer

A simple file header-only qt helper library for serializing/deserializing
QSharedPointer\<QObject\> into/from QVariantMap. Also support
serializing/deserializing QList\<QSharedPointer\<QObject\>\> and
QMap\<QString, QSharedPointer\<QObject\>\> into/from QVariantList and
QVariantMap.

As QVariantMap and QVariantList can easily be converted to/from Qt JSON types
and QDBusArgument, this library should be good enough for common usage.

Check tests for coding examples.
