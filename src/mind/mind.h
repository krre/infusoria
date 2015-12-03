#include <QtCore>

class Mind : public QObject
{
    Q_OBJECT
public:
    explicit Mind(const QString& filePath);
    void start();
    void stop();

signals:

private:
    QString filePath;
};
