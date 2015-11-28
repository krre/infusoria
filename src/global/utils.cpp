#include "utils.h"

bool Utils::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    return checkFile.exists() && checkFile.isFile();
}

bool Utils::removeFile(const QString& filePath)
{
    return QFile::remove(filePath);
}
