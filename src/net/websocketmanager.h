#pragma once
#include <QtCore>
#include <QtWebSockets>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebSocketManager : public QObject
{
    Q_OBJECT
public:
    WebSocketManager();
    ~WebSocketManager() { qDebug() << "WebSocketManager destructor"; }

private slots:
    void onAcceptError(QAbstractSocket::SocketError socketError);
    void onServerError(QWebSocketProtocol::CloseCode closeCode);
    void onNewConnection();

private:
    QWebSocketServer* wss;
    QWebSocket* ws;
};
