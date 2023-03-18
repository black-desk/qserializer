#pragma once

#include <QObject>                        // for Q_PROPERTY, QObject, Q_OBJECT
#include <QString>                        // for QString
#include <qserializer/qserializer_dbus.h> // for move_in, move_out, QSERIAL...

class Response : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString msg MEMBER msg);
        Q_PROPERTY(int code MEMBER code);

    public:
        QString msg;
        int code;
};

QSERIALIZER_DECLARE_DBUS(Response);
