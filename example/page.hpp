#pragma once

#include "base.hpp"
#include "QSerializer"

class Page : public Base {
        Q_OBJECT;
        Q_PROPERTY(int number MEMBER m_number);

    public:
        int m_number;
};

Q_DECLARE_SERIALIZER(Page);
