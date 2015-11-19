#include "websocketmanager.h"
#include "../global/macro.h"

WebSocketManager::WebSocketManager()
{
    server = new QWebSocketServer("Infusoria", QWebSocketServer::NonSecureMode, this);
    connect(server, &QWebSocketServer::acceptError, this, &WebSocketManager::onAcceptError);
    connect(server, &QWebSocketServer::serverError, this, &WebSocketManager::onServerError);
    connect(server, &QWebSocketServer::newConnection, this, &WebSocketManager::onNewConnection);
    connect(server, &QWebSocketServer::closed, this, &WebSocketManager::closed);
    server->listen();
    console("Infusoria AI unit started. Port " << server->serverPort());
}

WebSocketManager::~WebSocketManager() {
    console("WebSocketManager destructor");
    server->close();
    qDeleteAll(clients.begin(), clients.end());
}

void WebSocketManager::onAcceptError(QAbstractSocket::SocketError socketError)
{
    console("Accept error: " << socketError);
}

void WebSocketManager::onServerError(QWebSocketProtocol::CloseCode closeCode)
{
    console("Server error: " << closeCode);
}

void WebSocketManager::onNewConnection()
{
    console("New connection");
    QWebSocket *socket = server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketManager::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketManager::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketManager::socketDisconnected);

    clients << socket;
}

void WebSocketManager::processTextMessage(QString message)
{
    QWebSocket *client = qobject_cast<QWebSocket*>(sender());
    if (client) {
        client->sendTextMessage(message);
    }
}

void WebSocketManager::processBinaryMessage(QByteArray message)
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        client->sendBinaryMessage(message);
    }
}

void WebSocketManager::socketDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        clients.removeAll(client);
        client->deleteLater();
    }
}
