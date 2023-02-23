#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

#include "Book"
#include "Page"

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

        QSharedPointer<Book> book(new Book());
        auto map = doc.object().toVariantMap();
        QMetaType::convert(QMetaType::fromType<QVariantMap>(), &map,
                           QMetaType::fromType<QSharedPointer<Book> >(), &book);
        QMetaType::convert(QMetaType::fromType<QSharedPointer<Book> >(), &book,
                           QMetaType::fromType<QVariantMap>(), &map);

        qDebug() << QJsonObject::fromVariantMap(map);

        return 0;
}
