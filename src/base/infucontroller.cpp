#include "infucontroller.h"

InfuController::InfuController(QObject *parent) : QObject(parent)
{

}

void InfuController::startInfusoria(const QString& filePath)
{
    Infusoria* infusoria = new Infusoria(filePath);
    infusoria->start();
    infusories[infusoria->uuid()] = infusoria;
}

void InfuController::stopInfusoria(const QString& uuid)
{
    Infusoria* infusoria = infusories[uuid];
    infusoria->stop();
    delete infusoria;
    infusories.remove(uuid);
}
