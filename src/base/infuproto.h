#pragma once

class QString;
class QJsonDocument;
class QWebSocket;

class InfuProto {
public:
    InfuProto();
    static void send(const QString& message);
    static void send(QJsonDocument& message, QWebSocket* client);
    static void receive(const QString& message, QWebSocket* client);
};
