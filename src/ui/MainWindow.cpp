#include "MainWindow.h"
#include <QMenuBar>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resize(800, 600);
    createActions();
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, qApp, &QCoreApplication::quit);
}
