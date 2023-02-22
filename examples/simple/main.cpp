#include <QJsonObject>
#include <QVariant>

#include "Book"
#include "Page"

int main()
{
        Page p;
        p.m_number = 1;
        QVariant v;
        v.setValue(&p);
        qDebug() << QJsonObject::fromVariantMap(v.toMap());

        Book book;
        book.m_title = "title";
        book.m_pages.push_back(&p);

        book.m_dict["a"] = &p;

        v.setValue(&book);
        qDebug() << QJsonObject::fromVariantMap(v.toMap());

        return 0;
}
