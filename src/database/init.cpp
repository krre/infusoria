#include "init.h"
#include <app.h>

bool Init::create(const QString& filePath, const QVariantMap& individuality)
{
    QFileInfo checkFile(filePath);
    if (checkFile.exists() && checkFile.isFile()) {
        qDebug() << "File is exist";
        return false;
    }

    qDebug() << individuality;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
             return false;
        }
        initTables(db);
        initRecords(db);
    }
    QSqlDatabase::removeDatabase(filePath);
    qDebug() << QString("AI unit created successfully in %1").arg(filePath);
    return true;
}

void Init::initTables(const QSqlDatabase& db)
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs("
               "name,"
               "value"
               ")");
}

void Init::initRecords(const QSqlDatabase& db)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    query.bindValue(":name", "version");
    query.bindValue(":value", App::version());
    bool result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}
