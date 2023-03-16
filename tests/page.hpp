#pragma once

#include <qserializer/qserializer.h>

#include "base.hpp"

class Page : public Base {
        Q_OBJECT;
        Q_PROPERTY(int number MEMBER m_number);

    public:
        int m_number;
};

QSERIALIZER_DECLARE(Page);
