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
    ~WebSocketManager();

signals:
    void closed();

private slots:
    void onAcceptError(QAbstractSocket::SocketError socketError);
    void onServerError(QWebSocketProtocol::CloseCode closeCode);
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer* server;
    QList<QWebSocket*> clients;
};
