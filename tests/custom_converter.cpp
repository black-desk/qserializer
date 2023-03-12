#include "custom_converter.hpp"

#include <mutex>

#include <QVariantList>

void registerQListQStringConveter()
{
        static std::once_flag flag;
        std::call_once(flag, []() {
                QMetaType::registerConverter<QList<QString>, QVariantList>(
                        [](const QList<QString> &from) -> QVariantList {
                                return QVariant(QStringList(from)).toList();
                        });
                QMetaType::registerConverter<QVariantList, QList<QString>>(
                        [](const QVariantList &from) -> QList<QString> {
                                return QVariant(from).value<QStringList>();
                        });
        });
}
