#include "Organism.h"
#include "database/Database.h"

Organism::Organism(QObject* parent) : QObject(parent) {
    m_database = new Database(this);
}

void Organism::create(const QString& name, const QString& directory) {
    open(directory + "/" + name + ".db");
    m_database->updateMetaValue("name", name);
}

void Organism::open(const QString& filePath) {
    m_database->open(filePath);
}

QString Organism::filePath() const {
    return m_database->filePath();
}

QString Organism::name() const {
    return m_database->metaValue("name").toString();
}
