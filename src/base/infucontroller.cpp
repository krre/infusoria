#include "infucontroller.h"

InfuController::InfuController(QObject *parent) : QObject(parent)
{

}

void InfuController::startInfusoria(const QString& filePath)
{
    qDebug() << "start" << filePath;
}

void InfuController::stopInfusoria(const QString& filePath)
{
    qDebug() << "stop" << filePath;
}
