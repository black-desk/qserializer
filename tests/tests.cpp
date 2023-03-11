#include <gtest/gtest.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

#include "book.hpp"

TEST(QSerializer, Basic)
{
        QJsonDocument doc = QJsonDocument::fromJson(QString(R"({
                "title": "Some title",
                "pages": [
                        {
                                "number": 1
                        },
                        {
                                "number": 2
                        }
                ],
                "dict": null
        })")
                                                            .toUtf8());

        QSharedPointer<Book> book;

        QVariant v = doc.object().toVariantMap();
        book = v.value<QSharedPointer<Book>>();

        EXPECT_NE(book, nullptr);
        EXPECT_EQ(book->m_title, "Some title");
        EXPECT_EQ(book->m_pages.length(), 2);
        EXPECT_EQ(book->m_pages[0]->m_number, 1);
        EXPECT_EQ(book->m_pages[1]->m_number, 2);
        EXPECT_EQ(book->m_dict.size(), 0);

        v.fromValue(book);

        doc = QJsonDocument(QJsonObject::fromVariantMap(v.toMap()));

        QSharedPointer<Book> book2;

        v = doc.object().toVariantMap();
        book2 = v.value<QSharedPointer<Book>>();

        EXPECT_NE(book2, nullptr);
        EXPECT_EQ(book2->m_title, "Some title");
        EXPECT_EQ(book2->m_pages.length(), 2);
        EXPECT_EQ(book2->m_pages[0]->m_number, 1);
        EXPECT_EQ(book2->m_pages[1]->m_number, 2);
        EXPECT_EQ(book2->m_dict.size(), 0);
}
