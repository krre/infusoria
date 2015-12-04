#include "infusoria.h"

Infusoria::Infusoria(const QString& filePath) : filePath(filePath)
{
}

void Infusoria::start()
{
    qDebug() << "Infusoria started with" << filePath;
}

void Infusoria::stop()
{
    qDebug() << "Infusoria stopped with" << filePath;
}
