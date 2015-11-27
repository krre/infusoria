#include "utils.h"

bool Utils::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    return checkFile.exists() && checkFile.isFile();
}
