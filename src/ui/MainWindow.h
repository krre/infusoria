#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void showAbout();

private:
    void createActions();
};
