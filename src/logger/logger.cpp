#include "logger.h"

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    qDebug() << "logger";
}

Logger::~Logger()
{
    qDebug() << "~logger";
}
