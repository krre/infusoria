#include "logger.h"
#include <settings.h>
#include "../base/infuproto.h"

extern QPointer<Settings> settings;

Logger& Logger::instance()
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

    QString text;
    QTextStream ts(&text);
    ts << QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "\n";
    ts << buffer.trimmed() << "\n\n";
    InfuProto::send(text);

    QFile data(logPath());
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << text;
        out.flush();
    }
}
