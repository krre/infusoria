#include "websocketmanager.h"

WebSocketManager::WebSocketManager()
{
    wss = new QWebSocketServer("infusoria", QWebSocketServer::NonSecureMode, this);
    wss->listen();
    qDebug() << wss->serverAddress() << wss->serverPort();
}
