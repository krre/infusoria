#pragma once
#include <QtCore>
#include "../mind/mind.h"

class InfuController : public QObject
{
    Q_OBJECT
public:
    explicit InfuController(QObject *parent = 0);
    Q_INVOKABLE void startInfusoria(const QString& filePath);
    Q_INVOKABLE void stopInfusoria(const QString& filePath);

signals:

private:
    QHash<QString, Mind*> infusories;
    WebSocketManager webSocketManager;
};
