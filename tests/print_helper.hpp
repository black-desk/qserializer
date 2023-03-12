#pragma once

#include <iostream>

#include <QDebug>
#include <QString>

template <typename T>
std::enable_if_t<!std::is_same<T, std::string>::value, std::ostream &>
operator<<(std::ostream &os, const T &x)
{
        QString buf;
        {
                QDebug debug(&buf);
                debug << x;
        }
        os << buf.toStdString();
        return os;
}
