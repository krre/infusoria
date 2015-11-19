#include "repl.h"
#include "../global/macro.h"

Repl::Repl(const QString& filePath) : filePath(filePath)
{

}

void Repl::run()
{
    console("REPL run with " << filePath.toStdString());
}

