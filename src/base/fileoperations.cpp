#include "fileoperations.h"

FileOperations::FileOperations()
{

}

void FileOperations::saveInfuList(const QString& filePath, const QStringList& list)
{
    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        for (int i = 0; i < list.size(); ++i) {
            stream << list.at(i) << '\n';
        }
    } else {
        qDebug() << "Error opening file";
    }
    file.close();
}

QStringList FileOperations::loadInfuList(const QString& filePath)
{
    QStringList list;
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            list += stream.readLine();
        }
        return list;
    } else {
        return QStringList();
    }
}
