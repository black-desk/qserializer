#include "server.h"

#include <qcoreapplication.h>

#include "serveradaptor.h"

Server::Server(QObject *parent)
        : QObject(parent)
{
        new DBusServerAdaptor(this);
        QDBusConnection::sessionBus().registerObject("/", this);
        QDBusConnection::sessionBus().registerService("my.test.DBusServer");
}

Server::~Server() = default;

QMap<QString, QSharedPointer<Response>> Server::ping()
{
        auto resp = QSharedPointer<Response>(new Response);
        resp->msg = "message";
        resp->code = 2;
        return { { "resp", resp } };
}

int main(int argc, char **argv)
{
        Server s;
        QCoreApplication app(argc, argv);
        return app.exec();
}
