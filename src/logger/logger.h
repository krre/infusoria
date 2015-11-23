#pragma once
#include <QtCore>
#include <iostream>

#define LOGGER() Logger::Helper().stream()

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& instance();
    void setInfuFile(QFileInfo& fileInfo);

    class Helper
    {
    public:
        explicit Helper() : debug(&buffer) {}
        ~Helper() { write(); }
        QDebug& stream(){ return debug; }

    private:
        void write() {
            std::cout << QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
            std::cout << buffer.trimmed().toStdString() << std::endl << std::endl;
        }
        QString buffer;
        QDebug debug;
    };

private:
    Logger();
    ~Logger();
    QString directory;
    QString name;
};
