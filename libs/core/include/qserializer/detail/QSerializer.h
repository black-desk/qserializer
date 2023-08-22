#pragma once

#include <type_traits> // for is_base_of, is_pointer

#include <QDebug>           // for QDebug
#include <QList>            // for QList
#include <QLoggingCategory> // for qCCritical, Q_LOGGING_CATEGORY
#include <QMap>             // for QMap, operator!=, operator==
#include <QMessageLogger>   // for QMessageLogger
#include <QMetaObject>      // for QMetaObject
#include <QMetaProperty>    // for QMetaProperty
#include <QMetaType>        // for QMetaType
#include <QSharedPointer>   // for QSharedPointer
#include <QString>          // for QString
#include <QVariant>         // for QVariant
#include <QVariantList>     // for QVariantList
#include <QVariantMap>      // for QVariantMap

class QObject;
template <class T>
class QSharedPointer;

namespace qserializer::detail
{

static inline Q_LOGGING_CATEGORY(log, "qserializer");

template <typename T>
class QSerializer {
    public:
        static_assert(!std::is_const_v<T>,
                      "QSerializer shouldn't instantiation with constant type.");
        static_assert(
                !std::is_reference_v<T>,
                "QSerializer shouldn't instantiation with reference type.");
        static void registerConverters();

    private:
        static QVariantMap ToQVariantMap(const T &from) noexcept;
        static T FromQVariantMap(const QVariantMap &map) noexcept;

        static QVariantList ListToQVariantList(const QList<T> &list) noexcept;
        static QList<T> ListFromQVariantList(const QVariantList &list) noexcept;

        static QVariantMap
        TMapToQVariantMap(const QMap<QString, T> &map) noexcept;
        static QMap<QString, T>
        TMapFromQVariantMap(const QVariantMap &map) noexcept;
};

template <typename T>
void QSerializer<T>::registerConverters()
{
        QMetaType::registerConverter<T, QVariantMap>(ToQVariantMap);
        QMetaType::registerConverter<QVariantMap, T>(FromQVariantMap);

        QMetaType::registerConverter<QList<T>, QVariantList>(
                ListToQVariantList);
        QMetaType::registerConverter<QVariantList, QList<T>>(
                ListFromQVariantList);

        QMetaType::registerConverter<QMap<QString, T>, QVariantMap>(
                TMapToQVariantMap);
        QMetaType::registerConverter<QVariantMap, QMap<QString, T>>(
                TMapFromQVariantMap);
}

template <typename T>
QVariantMap QSerializer<T>::ToQVariantMap(const T &from) noexcept
{
        auto ret = QVariantMap{};

        if (std::is_pointer_v<T>(from)) {
                if (from == nullptr) {
                        return ret;
                }
        }

        static const QMetaObject *const metaObject =
                QMetaType::fromType<T>().metaObject();
        assert(("qserializer: pointer to metaObject is nullptr.",
                metaObject != nullptr));

        for (int i = 0; i < metaObject->propertyCount(); i++) {
                const char *k = metaObject->property(i).name();
                QVariant v =
                        std::is_base_of_v<T, QObject> ?
                                metaObject->property(i).read(&from) :
                                metaObject->property(i).readOnGadget(&from);
                if (v.canConvert<QString>()) {
                        ret.insert(k, v);
                        continue;
                }
                if (v.canConvert<QVariantList>()) {
                        ret.insert(k, v.value<QVariantList>());
                        continue;
                }
                if (v.canConvert<QVariantMap>()) {
                        ret.insert(k, v.value<QVariantMap>());
                        continue;
                }
                qCCritical(log).noquote()
                        << QString("Failed to insert \"%1\", maybe missing converter")
                                   .arg(k);
        }
        return ret;
}

template <typename T>
T QSerializer<T>::FromQVariantMap(const QVariantMap &map) noexcept
{
        QSharedPointer<std::remove_const_t<T>> ret(
                new std::remove_const_t<T>());

        static const QMetaObject *const metaObject =
                QMetaType::fromType<std::remove_const_t<T> *>().metaObject();
        assert(("qserializer: pointer to metaObject is nullptr.",
                metaObject != nullptr));

        for (int i = 0; i < metaObject->propertyCount(); i++) {
                QMetaProperty metaProp = metaObject->property(i);

                const char *metaPropName = metaProp.name();
                QVariantMap::ConstIterator it = map.find(metaPropName);
                if (it == map.end()) {
                        continue;
                }

                const bool &writeResult =
                        std::is_base_of_v<T, QObject> ?
                                metaProp.write(&ret, it.value()) :
                                metaProp.writeOnGadget(&ret, it.value());

                if (writeResult) {
                        continue;
                }

                qCCritical(log).noquote()
                        << QString("Failed to write \"%1\" [%2] , maybe missing converter")
                                   .arg(metaPropName)
                                   .arg(metaProp.typeName());
        }
        return ret;
}

template <typename T>
QVariantList QSerializer<T>::ListToQVariantList(const QList<T> &list) noexcept
{
        auto ret = QVariantList{};
        for (auto const &item : list) {
                ret.push_back(PToQVariantMap(item));
        }
        return ret;
}

template <typename T>
QList<T> QSerializer<T>::ListFromQVariantList(const QVariantList &list) noexcept
{
        auto ret = QList<T>{};
        for (auto const &item : list) {
                ret.push_back(FromQVariantMap(item.toMap()));
        }
        return ret;
}

template <typename T>
QVariantMap
QSerializer<T>::TMapToQVariantMap(const QMap<QString, T> &map) noexcept
{
        auto ret = QVariantMap{};
        for (auto it = map.begin(); it != map.end(); it++) {
                ret.insert(it.key(), PToQVariantMap(it.value()));
        }
        return ret;
}

template <typename T>
QMap<QString, T>
QSerializer<T>::TMapFromQVariantMap(const QVariantMap &map) noexcept
{
        auto ret = QMap<QString, T>{};
        for (auto it = map.begin(); it != map.end(); it++) {
                ret.insert(it.key(),
                           std::move(FromQVariantMap(it.value().toMap())));
        }
        return ret;
}

}
