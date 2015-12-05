#include "infuproto.h"
#include "../logger/logger.h"
#include "infucontroller.h"
#include "fileoperations.h"

extern QPointer<InfuController> infuController;

InfuProto::InfuProto()
{

}

void InfuProto::send(QJsonDocument& message, QWebSocket* client)
{
    QJsonObject obj = message.object();
    obj["sender"] = "IM";
    message.setObject(obj);
    QString textMessage(message.toJson());
    client->sendTextMessage(textMessage);
    LOGGER() << QString("SEND to IP=") + client->peerAddress().toString()
             << QString("PORT=") + QString::number(client->peerPort()) + ":"
             << (obj["action"].toString() == "getLog" ? "Log" : textMessage);
}

void InfuProto::receive(const QString& message, QWebSocket* client)
{
    LOGGER() << QString("RECEIVE from IP=") + client->peerAddress().toString() << QString("PORT=") + QString::number(client->peerPort()) + ":" << message;

    QByteArray ba;
    ba.append(message);
    QJsonDocument receiveDoc = QJsonDocument::fromJson(ba);
    QString sender = receiveDoc.object()["sender"].toString();
    QString action = receiveDoc.object()["action"].toString();
    if (sender == "aquarium") {
        if (action == "getInfusories") {
            QHash<QString, Infusoria*>* infusories = infuController->online();
            QJsonObject obj;
            obj["action"] = action;
            QJsonArray array = QJsonArray::fromStringList(infusories->keys());
            obj["result"] = array;
            QJsonDocument sendDoc(obj);
            send(sendDoc, client);
        } else if (action == "getLog") {
            QJsonObject obj;
            obj["action"] = action;
            QJsonArray array = QJsonArray::fromStringList(FileOperations::loadList(Logger::Helper().logPath()));
            obj["result"] = array;
            QJsonDocument sendDoc(obj);
            send(sendDoc, client);
        }
    } else if (sender == "infusoria") {

    }
}

