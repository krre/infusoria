#include "websocketmanager.h"

WebSocketManager::WebSocketManager()
{
    wss = new QWebSocketServer("infusoria", QWebSocketServer::NonSecureMode, this);
    wss->listen();
    qDebug() << "Infusoria AI unit started. Port" << wss->serverPort();
}
