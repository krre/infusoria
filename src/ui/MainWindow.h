#pragma once
#include <QMainWindow>

class FileSettings;
class Dashboard;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();

    void showPreferences();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void createActions();

    FileSettings* m_fileSettings = nullptr;
    Dashboard* m_dashboard = nullptr;
};
