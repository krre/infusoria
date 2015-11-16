#include "mind.h"

Mind::Mind(const QString& filePath) : filePath(filePath)
{

}

void Mind::run()
{
    qDebug() << "run with" << filePath;
}
