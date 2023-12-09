#include "Init.h"
#include <App.h>
#include <QtSql>

bool Init::create(const QString& name, const QString& filePath, const QVariantMap& individuality) {
    QFileInfo checkFile(filePath);
    if (checkFile.exists() && checkFile.isFile()) {
        qDebug() << "File is exist";
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
        initRecords(db, name);
        addIndividuality(db, individuality);
    }
    QSqlDatabase::removeDatabase(filePath);
    qDebug() << QString("AI unit created successfully in %1").arg(filePath);
    return true;
}

void Init::setName(const QString& name, const QString& filePath) {
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
        }

        QSqlQuery query(db);
        query.prepare("UPDATE Defs SET value = :value WHERE name = :name");
        query.bindValue(":name", "name");
        query.bindValue(":value", name);

        bool result = query.exec();
        if (!result) {
            qDebug("Error occurred update record");
            qDebug("%s", qPrintable(query.lastError().text()));
        }
    }
    QSqlDatabase::removeDatabase(filePath);
}

QVariantMap Init::individuality(const QString& filePath) {
    QVariantMap map;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
        }
        QSqlQuery query(QString("SELECT * FROM Individuality"), db);
        while (query.next()) {
            map[query.value(0).toString()] = query.value(1).toString();
        }
    }
    QSqlDatabase::removeDatabase(filePath);

    return map;
}

void Init::initTables(const QSqlDatabase& db) {
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs(name, value)");
    query.exec("CREATE TABLE Individuality(name, value)");
}

void Init::initRecords(const QSqlDatabase& db, const QString& name) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    // Verison
    query.bindValue(":name", "version");
    query.bindValue(":value", App::version());
    bool result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }

    // Name
    query.bindValue(":name", "name");
    query.bindValue(":value", name);
    result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }

    // Uuid
    query.bindValue(":name", "uuid");
    query.bindValue(":value", QUuid::createUuid().toString());
    result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }

    // Birthday
    query.bindValue(":name", "birthday");
    query.bindValue(":value", QDateTime::currentMSecsSinceEpoch());
    result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}

void Init::addIndividuality(const QSqlDatabase& db, const QVariantMap& individuality) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Individuality (name, value) "
                  "VALUES (:name, :value)");

    QMapIterator<QString, QVariant> i(individuality);
    while (i.hasNext()) {

        i.next();
        query.bindValue(":name", i.key());
        query.bindValue(":value",  i.value());

        bool result = query.exec();
        if (!result) {
            qDebug("Error occurred insert record");
            qDebug("%s", qPrintable(query.lastError().text()));
        }
    }
}

QString Init::name(const QString &filePath) {
    QString name;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
             return "";
        }
        QSqlQuery query(QString("SELECT value FROM Defs WHERE name LIKE 'name'"), db);
        while (query.next()) {
            name = query.value(0).toString();
        }
    }
    QSqlDatabase::removeDatabase(filePath);
    return name;
}

QString Init::uuid(const QString &filePath) {
    QString uuid;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
             return "";
        }
        QSqlQuery query(QString("SELECT value FROM Defs WHERE name LIKE 'uuid'"), db);
        while (query.next()) {
            uuid = query.value(0).toString();
        }
    }
    QSqlDatabase::removeDatabase(filePath);
    return uuid;
}

QString Init::birthday(const QString& filePath) {
    QString birthday;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filePath);
        db.setDatabaseName(filePath);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
             return "";
        }
        QSqlQuery query(QString("SELECT value FROM Defs WHERE name LIKE 'birthday'"), db);
        while (query.next()) {
            birthday = query.value(0).toString();
        }
    }
    QSqlDatabase::removeDatabase(filePath);
    return birthday;
}
