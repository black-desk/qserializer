#pragma once

#include <mutex>

#include <QMap>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>

template <typename T> class QSerializer {
    public:
        static const QMetaObject *const mo;
        static void registerConverter()
        {
                QMetaType::registerConverter<T *, QVariantMap>(toQVariantMap);
                QMetaType::registerConverter<QVariantMap, T *>(fromQVariantMap);
                QMetaType::registerConverter<QList<T *>, QVariantList>(
                        QListTToQVariantList);
                QMetaType::registerConverter<QMap<QString, T *>, QVariantMap>(
                        QMapTToQVariantMap);
        }

        static QVariantMap toQVariantMap(T *from)
        {
                auto ret = QVariantMap{};
                for (int i = mo->propertyOffset(); i < mo->propertyCount();
                     i++) {
                        const char *k = mo->property(i).name();
                        QVariant v = mo->property(i).read(from);
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

        static T *fromQVariantMap(const QVariantMap &)
        {
                return nullptr;
        }

        static QVariantList QListTToQVariantList(QList<T *> fromList)
        {
                auto ret = QVariantList{};
                for (auto const &item : fromList) {
                        ret.push_back(toQVariantMap(item));
                }
                return ret;
        }

        static QVariantMap QMapTToQVariantMap(QMap<QString, T *> fromMap)
        {
                auto ret = QVariantMap{};
                for (auto it = fromMap.begin(); it != fromMap.end(); it++) {
                        ret.insert(it.key(), toQVariantMap(it.value()));
                }
                return ret;
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
