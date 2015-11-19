#include "websocketmanager.h"
#include "../global/macro.h"

WebSocketManager::WebSocketManager()
{
    wss = new QWebSocketServer("Infusoria", QWebSocketServer::NonSecureMode, this);
    connect(wss, &QWebSocketServer::acceptError, this, &WebSocketManager::onAcceptError);
    connect(wss, &QWebSocketServer::serverError, this, &WebSocketManager::onServerError);
    connect(wss, &QWebSocketServer::newConnection, this, &WebSocketManager::onNewConnection);
    wss->listen();
    console("Infusoria AI unit started. Port " << wss->serverPort());
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
