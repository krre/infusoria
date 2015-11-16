#include <QtCore>

class Mind : public QObject
{
    Q_OBJECT
public:
    explicit Mind(const QString& filePath);
    void run();

signals:

private:
    QString filePath;
};
