# QSerializer

A simple file header-only qt helper library for serializing/deserializing
QSharedPointer\<QObject\> into/from QVariantMap.

It have to be QSharedPointer of the QObject but not QObject. That's because
QObject has its copy constructor deleted. And I want to use the Qt meta type
system for meta programming. So I have to use some kind of pointer of QObject.
But QScopePointer cannot be moved. In the end I choose QScopePointer.

Also support serializing/deserializing QList\<QSharedPointer\<QObject\>\> and
QMap\<QString, QSharedPointer\<QObject\>\> into/from QVariantList and
QVariantMap.

As QVariantMap and QVariantList can easily be converted to/from Qt JSON types
and QDBusArgument, this library should be good enough for common usage.

Check tests for coding examples.
