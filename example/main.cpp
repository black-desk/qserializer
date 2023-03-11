#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

#include "book.hpp"
#include "page.hpp"

int main()
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

        qDebug() << "title:" << book->m_title;

        v.fromValue(book);

        qDebug() << v.toMap();
        qDebug() << QJsonObject::fromVariantMap(v.toMap());

        return 0;
}
