#include "logger.h"
#include <settings.h>

extern QPointer<Settings> settings;

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::Helper::write() {
    QString logDir = settings->value("Path", "log").toString();
    QDir dir;
    dir.mkdir(logDir);
    QString logPath = logDir + "/infu-" + QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd") + ".log";
    QFile data(logPath);
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "\n";
        out << buffer.trimmed() << "\n\n";
        out.flush();
    }
}
