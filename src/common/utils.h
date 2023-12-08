#pragma once
#include <QObject>
#include <QUrl>
#include <QStandardPaths>

class Utils : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString homePath READ homePath CONSTANT)

public:
    Q_INVOKABLE QString urlToPath(const QUrl& url) { return url.toLocalFile(); }
    Q_INVOKABLE QString urlToFileName(const QUrl& url) { return url.fileName(); }
    Q_INVOKABLE QUrl pathToUrl(const QString& path) { return QUrl::fromLocalFile(path); }
    Q_INVOKABLE QString pathToBaseName(const QString& path);
    QString homePath() { return QStandardPaths::writableLocation(QStandardPaths::HomeLocation); }
    Q_INVOKABLE static bool isFileExists(const QString& filePath);
    Q_INVOKABLE bool removeFile(const QString& filePath);
};
