#include <QtCore>

class Infusoria : public QObject
{
    Q_OBJECT
public:
    explicit Infusoria(const QString& filePath);
    void start();
    void stop();
    QString uuid() { return m_uuid; }
    QString name() { return m_name; }
    QString birthday() { return m_birthday; }
    QVariantMap individuality() { return m_individuality; }

signals:

private:
    QString filePath;
    QString m_uuid;
    QString m_name;
    QString m_birthday;
    QVariantMap m_individuality;
};
