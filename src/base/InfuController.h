#pragma once
#include <QObject>
#include <QHash>

class QWebSocket;
class Infusoria;

class InfuController : public QObject {
    Q_OBJECT
public:
    explicit InfuController(QObject* parent = 0);
    Q_INVOKABLE void startInfusoria(const QString& filePath);
    Q_INVOKABLE void stopInfusoria(const QString& uuid);
    QHash<QString, Infusoria*>* online() { return &infusories; }
    void addInfusorium(QWebSocket* infusorium) { m_infusoriums.append(infusorium); }
    void removeInfusorium(QWebSocket* infusorium) { m_infusoriums.removeOne(infusorium); }
    QList<QWebSocket*>* infusoriums() { return &m_infusoriums; }

signals:

private:
    QHash<QString, Infusoria*> infusories;
    QList<QWebSocket*> m_infusoriums;
};
