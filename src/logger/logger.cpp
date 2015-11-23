#include "logger.h"

QString Logger::directory;
QString Logger::name;

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

void Logger::Helper::write() {
    QString logPath = directory + "/" + name + "-" + QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd") + ".log";
    QFile data(logPath);
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "\n";
        out << buffer.trimmed() << "\n\n";
        out.flush();
    }
}
