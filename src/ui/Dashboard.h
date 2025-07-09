#pragma once
#include <QWidget>

class Organism;

class Dashboard : public QWidget {
public:
    Dashboard(const QString& name, const QString& directory);
    Dashboard(const QString& filePath);

    Organism* organism() const;

private:
    Organism* m_organism = nullptr;
};
