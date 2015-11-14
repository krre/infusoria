#pragma once
#include <QtCore>
#include <QtSql>

class Init : public QObject
{
    Q_OBJECT
public:
    Init() {}
    static bool create(const QString& path);

private:
    static void initTables(const QSqlDatabase& db);
    static void initRecords(const QSqlDatabase& db);
};
