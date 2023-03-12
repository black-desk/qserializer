#include <gtest/gtest.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

#include "book.hpp"
#include "print_helper.hpp"

TEST(QSerializer, Basic)
{
        auto sourceJson = QString(R"({
                "title": "Some title",
                "pages": [
                        { "number": 1 },
                        { "number": 2 }
                ],
                "dict": {
                        "page1": { "number": 1 },
                        "page2": { "number": 2 }
                },
                "list": [
                        "string1",
                        "string2",
                        "string3"
                ],
                "list2": [
                        "string1",
                        "string2",
                        "string3"
                ]
        })")
                                  .toUtf8();

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(sourceJson, &err);
        ASSERT_EQ(err.error, QJsonParseError::NoError);

        QVariant v = doc.object().toVariantMap();
        auto book = v.value<QSharedPointer<Book>>();

        ASSERT_NE(book, nullptr);
        ASSERT_EQ(book->m_title, "Some title");
        ASSERT_EQ(book->m_pages.length(), 2);
        ASSERT_EQ(book->m_pages[0]->m_number, 1);
        ASSERT_EQ(book->m_pages[1]->m_number, 2);
        ASSERT_EQ(book->m_dict.size(), 2);
        ASSERT_EQ(book->m_dict["page1"]->m_number, 1);
        ASSERT_EQ(book->m_dict["page2"]->m_number, 2);
        ASSERT_EQ(book->m_list1.size(), 3);
        ASSERT_EQ(book->m_list1[0], "string1");
        ASSERT_EQ(book->m_list1[1], "string2");
        ASSERT_EQ(book->m_list1[2], "string3");
        ASSERT_EQ(book->m_list2.size(), 3);
        ASSERT_EQ(book->m_list2[0], "string1");
        ASSERT_EQ(book->m_list2[1], "string2");
        ASSERT_EQ(book->m_list2[2], "string3");

        auto vmap = v.fromValue(book).toMap();
        ASSERT_EQ(vmap.value("title").toString(), "Some title");
        ASSERT_EQ(vmap.value("pages").toList().size(), 2);
        ASSERT_EQ(
                vmap.value("pages").toList()[0].toMap().value("number").toInt(),
                1);
        ASSERT_EQ(
                vmap.value("pages").toList()[1].toMap().value("number").toInt(),
                2);
        ASSERT_EQ(vmap.value("dict")
                          .toMap()
                          .value("page1")
                          .toMap()
                          .value("number")
                          .toInt(),
                  1);
        ASSERT_EQ(vmap.value("dict")
                          .toMap()
                          .value("page2")
                          .toMap()
                          .value("number")
                          .toInt(),
                  2);
        ASSERT_EQ(vmap.value("list").toStringList().size(), 3);
        ASSERT_EQ(vmap.value("list").toStringList()[0], "string1");
        ASSERT_EQ(vmap.value("list").toStringList()[1], "string2");
        ASSERT_EQ(vmap.value("list").toStringList()[2], "string3");
        ASSERT_EQ(vmap.value("list2").toStringList().size(), 3);
        ASSERT_EQ(vmap.value("list2").toStringList()[0], "string1");
        ASSERT_EQ(vmap.value("list2").toStringList()[1], "string2");
        ASSERT_EQ(vmap.value("list2").toStringList()[2], "string3");

        auto jsonObject = QJsonObject::fromVariantMap(vmap);

        auto expectedJson = QString(R"({
                "base": "",
                "title": "Some title",
                "pages": [
                        { "number": 1, "base": "" },
                        { "number": 2, "base": "" }
                ],
                "dict": {
                        "page1": { "number": 1, "base": "" },
                        "page2": { "number": 2, "base": "" }
                },
                "list": [
                        "string1",
                        "string2",
                        "string3"
                ],
                "list2": [
                        "string1",
                        "string2",
                        "string3"
                ]
        })")
                                    .toUtf8();
        doc = QJsonDocument::fromJson(expectedJson, &err);
        ASSERT_EQ(err.error, QJsonParseError::NoError);

        ASSERT_EQ(QJsonValue(jsonObject), QJsonValue(doc.object()));

        v = jsonObject.toVariantMap();

        auto book2 = v.value<QSharedPointer<Book>>();

        ASSERT_NE(book2, nullptr);
        ASSERT_EQ(book2->m_title, "Some title");
        ASSERT_EQ(book2->m_pages.length(), 2);
        ASSERT_EQ(book2->m_pages[0]->m_number, 1);
        ASSERT_EQ(book2->m_pages[1]->m_number, 2);
        ASSERT_EQ(book2->m_dict.size(), 2);
        ASSERT_EQ(book2->m_dict["page1"]->m_number, 1);
        ASSERT_EQ(book2->m_dict["page2"]->m_number, 2);
        ASSERT_EQ(book->m_list1.size(), 3);
        ASSERT_EQ(book2->m_list1[0], "string1");
        ASSERT_EQ(book2->m_list1[1], "string2");
        ASSERT_EQ(book2->m_list1[2], "string3");
        ASSERT_EQ(book->m_list2.size(), 3);
        ASSERT_EQ(book2->m_list2[0], "string1");
        ASSERT_EQ(book2->m_list2[1], "string2");
        ASSERT_EQ(book2->m_list2[2], "string3");
}
