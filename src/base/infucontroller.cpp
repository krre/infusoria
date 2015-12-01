#include "infucontroller.h"

InfuController::InfuController(QObject *parent) : QObject(parent)
{

}

void InfuController::startInfusoria(const QString& filePath)
{
    Mind* mind = new Mind(filePath);
    mind->start();
    infusories[filePath] = mind;
}

void InfuController::stopInfusoria(const QString& filePath)
{
    Mind* mind = infusories[filePath];
    mind->stop();
    delete mind;
    infusories.remove(filePath);
}
