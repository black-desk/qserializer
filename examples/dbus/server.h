#pragma once

#include <QMap>    // for QMap
#include <QObject> // for Q_CLASSINFO, QObject, Q_OBJECT, slots
#include <QString> // for QString

class Response;
template <class T>
class QSharedPointer;

class Server : public QObject {
        Q_OBJECT;
        Q_CLASSINFO("D-Bus Interface", "my.test.DBusServer");
        Q_CLASSINFO(
                "D-Bus Introspection",
                "  <interface name='my.test.DBusServer'>"
                "    <method name='ping'>"
                "      <annotation name='org.qtproject.QtDBus.QtTypeName.Out0' value='QMap&lt;QString,QSharedPointer&lt;Response&gt;&gt;'/>"
                "      <arg name='result' type='a{sa{sv}}' direction='out'/>"
                "    </method>"
                "  </interface>");

    public:
        Server(QObject *parent = nullptr);
        virtual ~Server();
    public slots:
        QMap<QString, QSharedPointer<Response>> ping();
};
