#pragma once
#include <QtCore>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& instance();
    void setDirectory(QFileInfo& fileInfo);

private:
    Logger();
    ~Logger();
    QString directory;
};
