#pragma once
#include <QObject>

class FileOperations : public QObject
{
    Q_OBJECT
public:
    FileOperations() {}
    Q_INVOKABLE static void saveList(const QString& filePath, const QStringList &list);
    Q_INVOKABLE static QStringList loadList(const QString& filePath);
};
