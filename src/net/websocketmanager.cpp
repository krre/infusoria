#include "websocketmanager.h"
#include "../global/macro.h"

WebSocketManager::WebSocketManager()
{
    server = new QWebSocketServer("Infusoria", QWebSocketServer::NonSecureMode, this);
    connect(server, &QWebSocketServer::acceptError, this, &WebSocketManager::onAcceptError);
    connect(server, &QWebSocketServer::serverError, this, &WebSocketManager::onServerError);
    connect(server, &QWebSocketServer::newConnection, this, &WebSocketManager::onNewConnection);
    server->listen();
    console("Infusoria AI unit started. Port " << server->serverPort());
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
}
