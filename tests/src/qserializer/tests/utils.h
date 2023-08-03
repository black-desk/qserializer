#pragma once

#include <string>      // for enable_if, enable_if_t, is_same
#include <type_traits> // for enable_if, enable_if_t, is_same

#include <QDebug>
#include <QString>

template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value,
                        std::ostream &>::type
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
