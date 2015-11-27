#pragma once
#include <QtCore>

#define MAJOR 0
#define MINOR 1
#define PATCH 0

class App : public QObject
{
    Q_OBJECT

public:
    static unsigned int major() { return MAJOR; }
    static unsigned int minor() { return MINOR; }
    static unsigned int patch() { return PATCH; }
    static QString version() { return QString("%1.%2.%3").arg(MAJOR).arg(MINOR).arg(PATCH); }
    static QString buildDate() { return QString(__DATE__); }
};
