#include <QtCore>

class Infusoria : public QObject
{
    Q_OBJECT
public:
    explicit Infusoria(const QString& filePath);
    void start();
    void stop();

signals:

private:
    QString filePath;
};
