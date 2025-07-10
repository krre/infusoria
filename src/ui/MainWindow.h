#pragma once
#include <QMainWindow>

class FileSettings;
class Dashboard;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

signals:
    void fileOpenChanged(bool isOpen);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();
    void open();

    void openFile(const QString& filePath);
    void closeFile();

    void showPreferences();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();

    FileSettings* m_fileSettings = nullptr;
    Dashboard* m_dashboard = nullptr;
};
