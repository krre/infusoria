#include "websocketmanager.h"

WebSocketManager::WebSocketManager()
{
    wss = new QWebSocketServer("Infusoria", QWebSocketServer::NonSecureMode, this);
    connect(wss, &QWebSocketServer::acceptError, this, &WebSocketManager::onAcceptError);
    connect(wss, &QWebSocketServer::serverError, this, &WebSocketManager::onServerError);
    connect(wss, &QWebSocketServer::newConnection, this, &WebSocketManager::onNewConnection);
    wss->listen();
    qDebug() << "Infusoria AI unit started. Port" << wss->serverPort();
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
    qDebug() << "New connection";
}
