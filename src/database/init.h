#pragma once
#include <QtCore>
#include <QtSql>

class Init : public QObject
{
    Q_OBJECT
public:
    Init() {}
    Q_INVOKABLE static bool create(const QString& filePath, const QVariantMap& individuality);

private:
    static void initTables(const QSqlDatabase& db);
    static void initRecords(const QSqlDatabase& db);
};
