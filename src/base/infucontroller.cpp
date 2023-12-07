#include "infucontroller.h"
#include "../infusoria/infusoria.h"

InfuController::InfuController(QObject* parent) : QObject(parent)
{

}

void InfuController::startInfusoria(const QString& filePath)
{
    Infusoria* infusoria = new Infusoria();
    connect(infusoria, &Infusoria::finished, infusoria, &QObject::deleteLater);
    infusoria->setFilePath(filePath);
    infusoria->start();
    infusories[infusoria->uuid()] = infusoria;
}

void InfuController::stopInfusoria(const QString& uuid)
{
    Infusoria* infusoria = infusories[uuid];
    infusoria->quit();
    infusories.remove(uuid);
}
