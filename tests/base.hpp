#pragma once

#include <QObject>                   // for QObject, Q_OBJECT, Q_PROPERTY
#include <QString>                   // for QString
#include <qserializer/qserializer.h> // for QSERIALIZER_DECLARE

class Base : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString base MEMBER m_base);

    public:
        QString m_base;
};

QSERIALIZER_DECLARE(Base);
