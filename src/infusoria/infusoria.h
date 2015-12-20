#include <QtCore>

class Infusoria : public QThread
{
    Q_OBJECT
public:
    void run() override;
    void setFilePath(const QString& filePath);
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
