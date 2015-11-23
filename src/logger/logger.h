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
        QDebug& stream() { return debug.noquote(); }

    private:
        void write();
        QString buffer;
        QDebug debug;
    };

private:
    Logger() {}
    static QString directory;
    static QString name;
};
