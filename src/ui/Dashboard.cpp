#include "Dashboard.h"
#include "organism/Organism.h"

Dashboard::Dashboard(const QString& name, const QString& directory) {
    m_organism = new Organism(this);
    m_organism->create(name, directory);
}

Dashboard::Dashboard(const QString& filePath) {
    m_organism = new Organism(this);
    m_organism->open(filePath);
}

Organism* Dashboard::organism() const {
    return m_organism;
}
