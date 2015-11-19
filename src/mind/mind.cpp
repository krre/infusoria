#include "mind.h"
#include "../global/macro.h"

Mind::Mind(const QString& filePath) : filePath(filePath)
{

}

void Mind::run()
{
    console("Mind run with " << filePath.toStdString());
}
