#pragma once
#include <QSqlDatabase>

class Database : public QObject {
public:
    Database(QObject* parent = nullptr);
    ~Database() override;

    void open(const QString& filePath);
    QString filePath() const;

    QSqlQuery exec(const QString& sql, const QVariantMap& params = QVariantMap()) const;

    void updateMetaValue(const QString& name, const QVariant& value) const;
    QVariant metaValue(const QString& name) const;

private:
    QSqlDatabase m_db;
};
