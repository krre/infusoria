#include "mind.h"
#include "../global/macro.h"

Mind::Mind(const QString& filePath) : filePath(filePath), sharedMemory("infusoria")
{
}

Mind::~Mind()
{
    if (sharedMemory.isAttached()) {
        sharedMemory.detach();
    }
}

void Mind::run()
{
    sharedMemory.attach();
    int maxNumPort = qPow(2, 16);
    bool isFirst = false;
    if (!sharedMemory.size()) {
        sharedMemory.create(sizeof(quint16) * maxNumPort);
        isFirst = true;
    }

    sharedMemory.lock();
    quint16* data = (quint16*)sharedMemory.data();

    if (isFirst) {
        data[0] = webSocketManager.serverPort();
        data[1] = 0;
    } else {
        for (int i = 0; i < maxNumPort; i++) {
            qDebug() << data[i];
            if (data[i] == 0) {
                data[i] = webSocketManager.serverPort();
                data[i + 1] = 0;
                break;
            }
        }
    }

    sharedMemory.unlock();
    console("Mind run with " << this->filePath.toStdString());
}
