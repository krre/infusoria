#include "infusoria.h"
#include "../logger/logger.h"
#include "../database/init.h"
#include <QTimer>

void Infusoria::run()
{
    LOGGER() << "Infusoria started with" << filePath;
    heartBeatTimer = new QTimer();
    connect(heartBeatTimer, &QTimer::timeout, this, &Infusoria::onTimeoutHeartBeat);
    heartBeatTimer->start(heartBeatInterval);
    exec();
    LOGGER() << "Infusoria stopped with" << filePath;
    delete heartBeatTimer;
}

void Infusoria::setFilePath(const QString& filePath) {
    this->filePath = filePath;
    m_name = Init::name(filePath);
    m_uuid = Init::uuid(filePath);
    m_birthday = Init::birthday(filePath);
    m_individuality = Init::individuality(filePath);
}

void Infusoria::onTimeoutHeartBeat()
{
//    qDebug() << "heart beat";
}
