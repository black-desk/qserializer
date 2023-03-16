#pragma once

#include <QObject>
#include <qserializer/qserializer_dbus.h>

class Response : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString msg MEMBER msg);
        Q_PROPERTY(int code MEMBER code);

    public:
        QString msg;
        int code;
};

QSERIALIZER_DECLARE_DBUS(Response);
