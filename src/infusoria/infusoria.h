#include <QtCore>

class Infusoria : public QObject
{
    Q_OBJECT
public:
    explicit Infusoria(const QString& filePath);
    void start();
    void stop();
    QUuid uuid() { return m_uuid; }
    QString name() { return m_name; }

signals:

private:
    QString filePath;
    QString m_uuid;
    QString m_name;
};
