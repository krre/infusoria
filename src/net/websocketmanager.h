#pragma once
#include <QtWebSockets>

class QWebSocketServer;
class QWebSocket;

class InfuController;

class WebSocketManager : public QObject
{
    Q_OBJECT
public:
    WebSocketManager();
    ~WebSocketManager();
    quint16 serverPort() { return server->serverPort(); }

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
    InfuController* infuController;
};
