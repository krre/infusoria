#pragma once
#include <QtCore>

class Repl : public QObject
{
    Q_OBJECT
public:
    explicit Repl(const QString& filePath);
    void run();

private:
    QString filePath;
};

