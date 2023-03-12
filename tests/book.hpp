#pragma once

#include <QList>
#include <QObject>
#include <QString>

#include "QSerializer"
#include "base.hpp"
#include "page.hpp"

class Book : public Base {
        Q_OBJECT;
        Q_PROPERTY(QString title MEMBER m_title);
        Q_PROPERTY(QList<QSharedPointer<Page> > pages MEMBER m_pages);
        Q_PROPERTY(QMap<QString, QSharedPointer<Page> > dict MEMBER m_dict);
        Q_PROPERTY(QStringList list MEMBER m_list);

    public:
        QString m_title;
        QList<QSharedPointer<Page> > m_pages;
        QMap<QString, QSharedPointer<Page> > m_dict;
        QStringList m_list;
};

Q_DECLARE_SERIALIZER(Book);
