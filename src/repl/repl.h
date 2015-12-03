#pragma once
#include <QtCore>

class Repl : public QObject
{
    Q_OBJECT
public:
    explicit Repl();
    void run();

private:
};

