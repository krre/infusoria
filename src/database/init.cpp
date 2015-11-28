#include "init.h"
#include "../global/app.h"
#include "../global/macro.h"

bool Init::create(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    if (checkFile.exists() && checkFile.isFile()) {
        console("File is exist");
        return false;
    }

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
    console("AI unit created successfully");
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
