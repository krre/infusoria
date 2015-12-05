#pragma once
#include <QtCore>

class FileOperations : public QObject
{
    Q_OBJECT
public:
    FileOperations();
    Q_INVOKABLE void saveInfuList(const QString& filePath, const QStringList &list);
    Q_INVOKABLE QStringList loadInfuList(const QString& filePath);
};
