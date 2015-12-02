#include "mind.h"

Mind::Mind(const QString& filePath) : filePath(filePath)
{
}

void Mind::start()
{
    qDebug() << "Mind started with" << filePath;
}

void Mind::stop()
{
    qDebug() << "Mind stopped with" << filePath;
}
