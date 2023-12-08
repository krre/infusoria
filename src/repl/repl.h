#pragma once
#include <QObject>

class Repl : public QObject {
    Q_OBJECT
public:
    explicit Repl();
    void run();

private:
};
