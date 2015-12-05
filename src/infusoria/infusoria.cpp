#include "infusoria.h"
#include "../logger/logger.h"

Infusoria::Infusoria(const QString& filePath) : filePath(filePath)
{
}

void Infusoria::start()
{
    LOGGER() << "Infusoria started with" << filePath;
}

void Infusoria::stop()
{
    LOGGER() << "Infusoria stopped with" << filePath;
}
