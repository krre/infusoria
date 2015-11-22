#pragma once
#include <QtCore>
#include <iostream>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& instance();
    void setDirectory(QFileInfo& fileInfo);

    class Helper
    {
    public:
        explicit Helper() : debug(&buffer) {}
        ~Helper() { write(); }
        QDebug& stream(){ return debug; }

    private:
        void write() { std::cout << buffer.trimmed().toStdString() << std::endl; }
        QString buffer;
        QDebug debug;
    };

private:
    Logger();
    ~Logger();
    QString directory;
};
