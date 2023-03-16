#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <qserializer/qserializer.h>

#include "base.hpp"
#include "page.hpp"

class Book : public Base {
        Q_OBJECT;
        Q_PROPERTY(QString title MEMBER m_title);
        Q_PROPERTY(QList<QSharedPointer<Page> > pages MEMBER m_pages);
        Q_PROPERTY(QMap<QString, QSharedPointer<Page> > dict MEMBER m_dict);
        Q_PROPERTY(QStringList list MEMBER m_list1);
        Q_PROPERTY(QList<QString> list2 MEMBER m_list2);
        Q_PROPERTY(QMap<QString, QSharedPointer<Book> > dict2 MEMBER m_dict2);

    public:
        QString m_title;
        QList<QSharedPointer<Page> > m_pages;
        QMap<QString, QSharedPointer<Page> > m_dict;
        QStringList m_list1;
        // NOTE: Qt cannot convert QList<QString> to QVariantList by default.
        // You need a custom converter registered to make QSerializer work,
        // check book.cpp for details.
        QList<QString> m_list2;
        QMap<QString, QSharedPointer<Book> > m_dict2;
};

QSERIALIZER_DECLARE(Book);
