#include "repl.h"

Repl::Repl(const QString& filePath) : filePath(filePath)
{

}

void Repl::run()
{
    qDebug() << "REPL run with" << filePath;
}

