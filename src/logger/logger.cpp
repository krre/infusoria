#include "logger.h"
#include <settings.h>

extern QPointer<Settings> settings;

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

QString Logger::Helper::logPath()
{
    QString logDir = settings->value("Path", "log").toString();
    QDir dir;
    dir.mkdir(logDir);
    return logDir + "/infu-" + QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd") + ".log";
}

void Logger::Helper::write() {

    QFile data(logPath());
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "\n";
        out << buffer.trimmed() << "\n\n";
        out.flush();
    }
}
