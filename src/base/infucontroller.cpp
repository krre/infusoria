#include "infucontroller.h"

InfuController::InfuController(QObject *parent) : QObject(parent)
{

}

void InfuController::startInfusoria(const QString& filePath)
{
    Infusoria* infusoria = new Infusoria(filePath);
    infusoria->start();
    infusories[filePath] = infusoria;
}

void InfuController::stopInfusoria(const QString& filePath)
{
    Infusoria* infusoria = infusories[filePath];
    infusoria->stop();
    delete infusoria;
    infusories.remove(filePath);
}
