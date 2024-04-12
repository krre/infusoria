#include "InfuProto.h"
#include "../logger/Logger.h"
#include "InfuController.h"
#include "FileOperations.h"
#include "../infusoria/Infusoria.h"
#include <QWebSocket>
#include <QtCore>

extern QPointer<InfuController> infuController;

InfuProto::InfuProto() {

}

void InfuProto::send(const QString& message) {
    if (!infuController->infusoriums()->count()) return;
    QJsonObject obj;
    obj["info"] = "log";
    obj["value"] = message;
    QJsonDocument sendDoc(obj);

    for (int i = 0; i < infuController->infusoriums()->count(); ++i) {
        send(sendDoc, infuController->infusoriums()->at(i));
    }
}

void InfuProto::send(QJsonDocument& message, QWebSocket* client) {
    QJsonObject obj = message.object();
    obj["sender"] = "IM";
    message.setObject(obj);
    QString textMessage(message.toJson());
    client->sendTextMessage(textMessage);
    /*
    LOGGER() << QString("SEND to IP=") + client->peerAddress().toString()
             << QString("PORT=") + QString::number(client->peerPort()) + ":"
             << (obj["action"].toString() == "getLog" ? "Log" : textMessage);
             */
}

void InfuProto::receive(const QString& message, QWebSocket* client) {
//    LOGGER() << QString("RECEIVE from IP=") + client->peerAddress().toString() << QString("PORT=") + QString::number(client->peerPort()) + ":" << message;

    QJsonDocument receiveDoc = QJsonDocument::fromJson(message.toUtf8());
    QString sender = receiveDoc.object()["sender"].toString();
    QString action = receiveDoc.object()["action"].toString();
    if (sender == "infusorium") {
        if (action == "getInfusories") {
            QHash<QString, Infusoria*>* infusories = infuController->online();
            QJsonObject obj;
            obj["action"] = action;
            QJsonArray array;

            QHashIterator<QString, Infusoria*> i(*infusories);
            while (i.hasNext()) {
                i.next();
                QJsonObject infu;
                infu["uuid"] = i.value()->uuid();
                infu["name"] = i.value()->name();
                array << infu;
            }

            obj["result"] = array;
            QJsonDocument sendDoc(obj);
            send(sendDoc, client);
        } else if (action == "getLog") {
            QJsonObject options = receiveDoc.object()["options"].toObject();
            if (options["enable"].toBool()) {
                infuController->addInfusorium(client);
                QJsonObject obj;
                obj["action"] = action;
                QJsonArray array = QJsonArray::fromStringList(FileOperations::loadList(Logger::Helper().logPath()));
                obj["result"] = array;
                QJsonDocument sendDoc(obj);
                send(sendDoc, client);
            } else {
                infuController->removeInfusorium(client);
            }
        } else if (action == "getInfusoria") {
            QJsonObject options = receiveDoc.object()["options"].toObject();
            QString uuid = options["uuid"].toString();
            QHash<QString, Infusoria*>* infusories = infuController->online();
            Infusoria* infusoria = infusories->operator [](uuid);

            QJsonObject obj;
            obj["action"] = action;
            QJsonObject objInfo;
            objInfo["name"] = infusoria->name();
            objInfo["uuid"] = uuid;
            objInfo["birthday"] = infusoria->birthday();
            objInfo["individuality"] = QJsonObject::fromVariantMap(infusoria->individuality());
            obj["result"] = objInfo;

            QJsonDocument sendDoc(obj);
            send(sendDoc, client);
        } else if (action == "message") {
            QJsonObject options = receiveDoc.object()["options"].toObject();
            QString message = "MESSAGE from Infusorium: " + options["message"].toString();
            qDebug() << message;
            LOGGER() << message;
        }
    } else if (sender == "infusoria") {

    }
}

