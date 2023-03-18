#pragma once

#include <QObject>                   // for Q_OBJECT, Q_PROPERTY
#include <QString>                   // for QString
#include <qserializer/qserializer.h> // for QSERIALIZER_DECLARE

#include "base.hpp" // for Base

class Page : public Base {
        Q_OBJECT;
        Q_PROPERTY(int number MEMBER m_number);

    public:
        int m_number;
};

QSERIALIZER_DECLARE(Page);
