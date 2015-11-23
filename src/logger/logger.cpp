#include "logger.h"

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::setInfuFile(QFileInfo &fileInfo)
{
    name = fileInfo.baseName();
    directory = fileInfo.dir().path() + "/log-" + name;
    QDir dir;
    dir.mkdir(directory);
}

Logger::Logger()
{
    qDebug() << "logger";
}

Logger::~Logger()
{
    qDebug() << "~logger";
}
