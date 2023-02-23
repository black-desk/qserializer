#pragma once

#include <mutex>

#include <QMap>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>

template <typename T>

class QSerializer {
    public:
        static const QMetaObject *const mo;
        static void registerConverter()
        {
                QMetaType::registerConverter<QSharedPointer<T>, QVariantMap>(
                        TtoQVariantMap);
                // QMetaType::registerConverter<QVariantMap, QSharedPointer<T> >(
                // QVariantMapToT);

                QMetaType::registerConverter<QList<QSharedPointer<T> >,
                                             QVariantList>(
                        QListTToQVariantList);
                QMetaType::registerConverter<QVariantList,
                                             QList<QSharedPointer<T> > >(
                        QVariantListToQListT);

                QMetaType::registerConverter<QMap<QString, QSharedPointer<T> >,
                                             QVariantMap>(QMapTToQVariantMap);
                QMetaType::registerConverter<
                        QVariantMap, QMap<QString, QSharedPointer<T> > >(
                        QVariantMapToQMapT);
        }

        static QVariantMap TtoQVariantMap(QSharedPointer<T> from)
        {
                auto ret = QVariantMap{};
                for (int i = mo->propertyOffset(); i < mo->propertyCount();
                     i++) {
                        const char *k = mo->property(i).name();
                        QVariant v = mo->property(i).read(from.data());
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
                }
                return ret;
        }

        static QSharedPointer<T> QVariantMapToT(const QVariantMap &map)
        {
                QSharedPointer<T> ret(new T());
                return ret;
        }

        static QVariantList QListTToQVariantList(QList<QSharedPointer<T> > list)
        {
                auto ret = QVariantList{};
                for (auto const &item : list) {
                        ret.push_back(TtoQVariantMap(item));
                }
                return ret;
        }

        static QList<QSharedPointer<T> > QVariantListToQListT(QVariantList list)
        {
                return {};
        }

        static QVariantMap
        QMapTToQVariantMap(QMap<QString, QSharedPointer<T> > map)
        {
                auto ret = QVariantMap{};
                for (auto it = map.begin(); it != map.end(); it++) {
                        ret.insert(it.key(), TtoQVariantMap(it.value()));
                }
                return ret;
        }
        static QMap<QString, QSharedPointer<T> >
        QVariantMapToQMapT(QVariantMap map)
        {
                return {};
        }
};

template <typename T>
const QMetaObject *const QSerializer<T>::mo =
        QMetaType(QMetaTypeId<T *>::qt_metatype_id()).metaObject();

#define Q_DECLARE_SERIALIZER(T)                  \
        Q_DECLARE_METATYPE(T *);                 \
        namespace QSerializerPrivateNamespace##T \
        {                                        \
                int init();                      \
                static int _ = init();           \
        };

#define Q_REGISTER_SERIALIZER(T)                                     \
        namespace QSerializerPrivateNamespace##T                     \
        {                                                            \
                int init()                                           \
                {                                                    \
                        static std::once_flag __flag;                \
                        std::call_once(__flag, []() {                \
                                QSerializer<T>::registerConverter(); \
                        });                                          \
                        return 0;                                    \
                }                                                    \
        }
