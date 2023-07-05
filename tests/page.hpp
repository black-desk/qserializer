#pragma once

#include <QMetaType>                 // for qRegisterMetaType
#include <QObject>                   // for Q_GADGET, Q_PROPERTY
#include <QSharedPointer>            // for QSharedPointer
#include <QString>                   // for QString
#include <qserializer/qserializer.h> // for QSERIALIZER_DECLARE

#include "base.hpp" // for Base

class Page : public Base {
        Q_GADGET;
        Q_PROPERTY(int number MEMBER m_number);

    public:
        int m_number;
};

QSERIALIZER_DECLARE(Page);
