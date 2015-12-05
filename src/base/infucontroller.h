#pragma once
#include <QtCore>
#include <QtWebSockets>
#include "../infusoria/infusoria.h"

class InfuController : public QObject
{
    Q_OBJECT
public:
    explicit InfuController(QObject *parent = 0);
    Q_INVOKABLE void startInfusoria(const QString& filePath);
    Q_INVOKABLE void stopInfusoria(const QString& filePath);
    QHash<QString, Infusoria*>* online() { return &infusories; }
    void addAquarium(QWebSocket* aquarium) { m_aquariums.append(aquarium); }
    void removeAquarium(QWebSocket* aquarium) { m_aquariums.removeOne(aquarium); }
    QList<QWebSocket*>* aquariums() { return &m_aquariums; }

signals:

private:
    QHash<QString, Infusoria*> infusories;
    QList<QWebSocket*> m_aquariums;
};
