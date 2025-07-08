#pragma once
#include <QSqlDatabase>

class Database : public QObject {
public:
    Database(QObject* parent = nullptr);
    ~Database() override;

    void create(const QString& filepath);
    void open(const QString& filepath);
    void close();
    bool isOpen() const;

    QSqlQuery exec(const QString& sql, const QVariantMap& params = QVariantMap()) const;

private:
    QSqlDatabase m_db;
};
