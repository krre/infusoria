#pragma once
#include <QtCore>
#include <QtSql>

class Init : public QObject
{
    Q_OBJECT
public:
    Init() {}
    Q_INVOKABLE static bool create(const QString& name, const QString& filePath, const QVariantMap& individuality);
    Q_INVOKABLE static QString name(const QString& filePath);
    Q_INVOKABLE static void setName(const QString& name, const QString& filePath);
    Q_INVOKABLE static QVariantMap individuality(const QString& filePath);

private:
    static void initTables(const QSqlDatabase& db);
    static void initRecords(const QSqlDatabase& db, const QString& name);
    static void addIndividuality(const QSqlDatabase& db, const QVariantMap& individuality);
};
