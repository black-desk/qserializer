#pragma once

#include <QObject>
#include <qserializer/qserializer.h>

class Base : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString base MEMBER m_base);

    public:
        QString m_base;
};

QSERIALIZER_DECLARE(Base);
