#include "custom_converter.h"

#include <QList>        // for QList
#include <QMetaType>    // for QMetaType
#include <QString>      // for QString
#include <QStringList>  // for QStringList
#include <QVariant>     // for QVariant
#include <QVariantList> // for QVariantList

void registerQListQStringConveter()
{
#if QT_VERSION <= QT_VERSION_CHECK(6, 2, 0)
        static int _ = []() -> int {
                QMetaType::registerConverter<QList<QString>, QVariantList>(
                        [](const QList<QString> &from) -> QVariantList {
                                return QVariant(QStringList(from)).toList();
                        });
                QMetaType::registerConverter<QVariantList, QList<QString>>(
                        [](const QVariantList &from) -> QList<QString> {
                                return QVariant(from).value<QStringList>();
                        });
                return _;
        }();
#endif
}
