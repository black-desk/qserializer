#include <QDBusConnection>   // for QDBusConnection
#include <QDBusPendingReply> // for QDBusPendingReply
#include <QDebug>            // for QDebug
#include <QMap>              // for QMap
#include <QSharedPointer>    // for QSharedPointer
#include <QtGlobal>          // for qDebug

#include "response.h"         // for Response
#include "server_interface.h" // for DBusServer

int main()
{
        my::test::DBusServer server(my::test::DBusServer::staticInterfaceName(),
                                    "/", QDBusConnection::sessionBus());
        auto resp = server.ping();
        auto value = resp.value();
        if (resp.isError() || !resp.isValid()) {
                return -1;
        }
        qDebug() << value["resp"]->msg << value["resp"]->code;
        return 0;
}
