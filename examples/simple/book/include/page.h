/* vim: set ft=cpp: */

#pragma once

#include "QSerializer"

class Page : public QObject {
        Q_OBJECT;
        Q_PROPERTY(int number MEMBER m_number);

    public:
        int m_number;
};

Q_DECLARE_SERIALIZER(Page);
