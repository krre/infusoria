#include "Utils.h"
#include <QFileInfo>

QString Utils::pathToBaseName(const QString& path) {
    QFileInfo fileInfo(path);
    return fileInfo.baseName();
}

bool Utils::isFileExists(const QString& filePath) {
    QFileInfo checkFile(filePath);
    return checkFile.exists() && checkFile.isFile();
}

bool Utils::removeFile(const QString& filePath) {
    return QFile::remove(filePath);
}

