#pragma once
#include <QObject>

class Database;

class Organism : public QObject {
public:
    Organism(QObject* parent);

    void create(const QString& name, const QString& directory);
    void open(const QString& filePath);

    QString filePath() const;
    QString name() const;

private:
    Database* m_database = nullptr;
};
