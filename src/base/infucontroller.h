#pragma once
#include <QtCore>
#include "../infusoria/infusoria.h"

class InfuController : public QObject
{
    Q_OBJECT
public:
    explicit InfuController(QObject *parent = 0);
    Q_INVOKABLE void startInfusoria(const QString& filePath);
    Q_INVOKABLE void stopInfusoria(const QString& filePath);
    QHash<QString, Infusoria*>* online() { return &infusories; }

signals:

private:
    QHash<QString, Infusoria*> infusories;
};
