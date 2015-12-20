#include "infusoria.h"
#include "../logger/logger.h"
#include "../database/init.h"

void Infusoria::run()
{
    LOGGER() << "Infusoria started with" << filePath;
    exec();
    LOGGER() << "Infusoria stopped with" << filePath;
}

void Infusoria::setFilePath(const QString& filePath) {
    this->filePath = filePath;
    m_name = Init::name(filePath);
    m_uuid = Init::uuid(filePath);
    m_birthday = Init::birthday(filePath);
    m_individuality = Init::individuality(filePath);
}
