#include "custom_converter.hpp"

#include <mutex>

#include <QVariantList>

void registerQListQStringConveter()
{
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
}
