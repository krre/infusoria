#include "infuproto.h"
#include "../logger/logger.h"
#include "infucontroller.h"

extern QPointer<InfuController> infuController;

InfuProto::InfuProto()
{

}

void InfuProto::send(QJsonDocument& message, QWebSocket* client)
{
    message.object()["sender"] = "IM";
    QString textMessage(message.toJson());
    client->sendTextMessage(textMessage);
    LOGGER() << QString("SEND to IP=") + client->localAddress().toString() << QString("PORT=") + QString::number(client->localPort()) + ":" << textMessage;
}

void InfuProto::receive(const QString& message, QWebSocket* client)
{
    LOGGER() << QString("RECEIVE from IP=") + client->localAddress().toString() << QString("PORT=") + QString::number(client->localPort()) + ":" << message;

    QByteArray ba;
    ba.append(message);
    QJsonDocument receiveDoc = QJsonDocument::fromJson(ba);
    QString sender = receiveDoc.object()["sender"].toString();
    QString action = receiveDoc.object()["action"].toString();
    if (sender == "aquarium") {
        if (action == "getInfusories") {
            QHash<QString, Infusoria*>* infusories = infuController->online();
            QJsonObject obj;
            obj["action"] = "getInfusories";
            QJsonArray array = QJsonArray::fromStringList(infusories->keys());
            obj["result"] = array;
            QJsonDocument sendDoc(obj);
            send(sendDoc, client);
        } else if (action == "getLog") {

        }
    } else if (sender == "infusoria") {

    }
}

