/* vim: set ft=cpp: */

#pragma once

#include <QList>
#include <QObject>
#include <QString>

#include "Page"
#include "QSerializer"

class Book : public QObject {
        Q_OBJECT;
        Q_PROPERTY(QString title MEMBER m_title);
        Q_PROPERTY(QList<Page *> pages MEMBER m_pages);
        Q_PROPERTY(QMap<QString, Page *> dict MEMBER m_dict);

    public:
        QString m_title;
        QList<Page *> m_pages;
        QMap<QString, Page *> m_dict;
};

Q_DECLARE_SERIALIZER(Book);
