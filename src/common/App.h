#pragma once
#include <QApplication>

class App : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(unsigned int major READ major CONSTANT)
    Q_PROPERTY(unsigned int minor READ minor CONSTANT)
    Q_PROPERTY(unsigned int patch READ patch CONSTANT)
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString applicationDirPath READ applicationDirPath CONSTANT)

public:
    static unsigned int major() { return MAJOR; }
    static unsigned int minor() { return MINOR; }
    static unsigned int patch() { return PATCH; }
    static QString version() { return QString("%1.%2.%3").arg(MAJOR).arg(MINOR).arg(PATCH); }
    static QString buildDate() { return QString("%1 %2").arg(__DATE__, __TIME__); }

private:
    QString qtVersion() { return QT_VERSION_STR; }
    QString applicationDirPath() { return qApp->applicationDirPath(); }
};
