#pragma once
#include <QObject>
#include <QDebug>

#define LOGGER() Logger::Helper().stream()

class Logger : public QObject {
    Q_OBJECT
public:
    static Logger& instance();

    class Helper
    {
    public:
        explicit Helper() : debug(&buffer) {}
        ~Helper() { write(); }
        QDebug& stream() { return debug.noquote(); }
        QString logPath();

    private:
        void write();
        QString buffer;
        QDebug debug;
    };

private:
    Logger() {}
};
