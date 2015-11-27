#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    void setValue(const QString& group, const QString& key, const QVariant& value);
    QVariant value(const QString& group, const QString& key, const QVariant& defaultValue = QVariant());

    void setMap(const QString& group, const QVariantMap& map);
    QVariantMap map(const QString& group);

    void setList(const QString& group, const QStringList& list);
    QStringList list(const QString& group);

private:
    QSettings* settings;

};
