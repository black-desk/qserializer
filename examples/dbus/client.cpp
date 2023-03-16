#include "server_interface.h"
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
