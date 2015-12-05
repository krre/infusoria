#include "websocketmanager.h"
#include <app.h>
#include <settings.h>
#include "../logger/logger.h"
#include "../base/infuproto.h"

extern QPointer<Settings> settings;

WebSocketManager::WebSocketManager()
{
    server = new QWebSocketServer("Infusoria", QWebSocketServer::NonSecureMode, this);
    connect(server, &QWebSocketServer::acceptError, this, &WebSocketManager::onAcceptError);
    connect(server, &QWebSocketServer::serverError, this, &WebSocketManager::onServerError);
    connect(server, &QWebSocketServer::newConnection, this, &WebSocketManager::onNewConnection);
    connect(server, &QWebSocketServer::closed, this, &WebSocketManager::closed);
    quint16 port = settings->value("Network", "port").toUInt();
    server->listen(QHostAddress::AnyIPv4, port);
    QString message = QString("%1 started on port %2").arg(App::name()).arg(server->serverPort());
    qDebug().noquote() << message;
    LOGGER() << message;
}

WebSocketManager::~WebSocketManager() {
    server->close();
    qDeleteAll(clients.begin(), clients.end());
}

void WebSocketManager::onAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Accept error:" << socketError;
}

void WebSocketManager::onServerError(QWebSocketProtocol::CloseCode closeCode)
{
    qDebug() << "Server error:" << closeCode;
}

void WebSocketManager::onNewConnection()
{
    QWebSocket* socket = server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketManager::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketManager::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketManager::socketDisconnected);

    clients << socket;

    LOGGER() << "Connection with" << socket->localAddress().toString();
}

void WebSocketManager::processTextMessage(QString message)
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if (client) {
        InfuProto::receive(message, client);
    }
}

void WebSocketManager::processBinaryMessage(QByteArray message)
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if (client) {
        client->sendBinaryMessage(message);
    }
}

void WebSocketManager::socketDisconnected()
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if (client) {
        clients.removeAll(client);
        client->deleteLater();
    }
}
