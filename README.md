# QSerializer

A qt helper header only library for (de)serializing QSharedPointer\<QObject\>
into/from QVariantMap. Also support (de)serializing
QList\<QSharedPointer\<QObject\>\> / QMap\<QString,QObject\> into/from
QVariantList/QVariantMap.

As QVariantMap and QVariantList can easily be converted to/from Qt JSON types
and QDBusArgument, this library should be good enough to go.

Check tests for usage examples.
