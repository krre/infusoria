#pragma once
#include <QtCore>
#include <QtWebSockets>

class InfuProto
{
public:
    InfuProto();
    static void send(QJsonDocument& message, QWebSocket* client);
    static void receive(const QString& message, QWebSocket* client);
};
