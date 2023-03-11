#pragma once

#include <QObject>

#include "QSerializer"

class Base : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString base MEMBER m_base);

    public:
        QString m_base;
};

Q_DECLARE_SERIALIZER(Base);
