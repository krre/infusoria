#pragma once
#include <QtCore>
#include <QtWebSockets>

class WebSocketManager : public QObject
{
    Q_OBJECT
public:
    WebSocketManager();

private:
    QWebSocketServer* wss;
    QWebSocket* ws;
};
