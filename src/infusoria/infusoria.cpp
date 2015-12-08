#include "infusoria.h"
#include "../logger/logger.h"
#include "../database/init.h"

Infusoria::Infusoria(const QString& filePath) : filePath(filePath)
{
}

void Infusoria::start()
{
    m_name = Init::name(filePath);
    m_uuid = Init::uuid(filePath);
    m_birthday = Init::birthday(filePath);
    m_individuality = Init::individuality(filePath);

    LOGGER() << "Infusoria started with" << filePath;
}

void Infusoria::stop()
{
    LOGGER() << "Infusoria stopped with" << filePath;
}
