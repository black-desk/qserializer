#pragma once

#include <QList>          // for QList
#include <QMap>           // for QMap
#include <QMetaType>      // for qRegisterMetaType
#include <QObject>        // for Q_PROPERTY, Q_GADGET
#include <QSharedPointer> // for QSharedPointer
#include <QString>        // for QString
#include <QStringList>    // for QStringList

#include "qserializer/core.h"             // for QSERIALIZER_DECLARE
#include "qserializer/tests/types/Base.h" // for Base
#include "qserializer/tests/types/Page.h" // for Page

template <class T>
class QSharedPointer;

namespace qserializer::tests::types
{

class Page;

class Book : public Base {
        Q_GADGET;
        Q_PROPERTY(QString title MEMBER m_title);
        // NOTE:
        // Qt5 can not found convertor
        // if type referenced in Q_PROPERTY is not global.
        Q_PROPERTY(QList<QSharedPointer<qserializer::tests::types::Page> > pages
                           MEMBER m_pages);
        Q_PROPERTY(
                QMap<QString, QSharedPointer<qserializer::tests::types::Page> >
                        dict MEMBER m_dict);
        Q_PROPERTY(QStringList list MEMBER m_list1);
        Q_PROPERTY(QList<QString> list2 MEMBER m_list2);
        Q_PROPERTY(
                QMap<QString, QSharedPointer<qserializer::tests::types::Book> >
                        dict2 MEMBER m_dict2);

    public:
        QString m_title;
        QList<QSharedPointer<Page> > m_pages;
        QMap<QString, QSharedPointer<Page> > m_dict;
        QStringList m_list1;
        // NOTE:
        // Qt5 cannot convert QList<QString> to QVariantList by default.
        // You need a custom converter registered to make QSerializer work,
        // check Book.cpp for details.
        QList<QString> m_list2;
        QMap<QString, QSharedPointer<Book> > m_dict2;
};

}

QSERIALIZER_DECLARE(qserializer::tests::types::Book);
