#pragma once
#include <QtCore>

#define MAJOR 0
#define MINOR 1
#define PATCH 0

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(unsigned int major READ major CONSTANT)
    Q_PROPERTY(unsigned int minor READ minor CONSTANT)
    Q_PROPERTY(unsigned int patch READ patch CONSTANT)
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

public:
    static unsigned int major() { return MAJOR; }
    static unsigned int minor() { return MINOR; }
    static unsigned int patch() { return PATCH; }
    static QString version() { return QString("%1.%2.%3").arg(MAJOR).arg(MINOR).arg(PATCH); }
    static QString name() { return QString("Infusoria Manager"); }
    static QString buildDate() { return QString(__DATE__); }

private:
    QString qtVersion() { return QT_VERSION_STR; }
};
