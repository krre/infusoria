#include "logger.h"

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::setDirectory(QFileInfo &fileInfo)
{
    this->directory = fileInfo.dir().path() + "/log-" + fileInfo.baseName();
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
