#pragma once
#include <QtCore>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& instance();

private:
    Logger();
    ~Logger();

signals:

public slots:
};
