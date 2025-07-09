#include "MainWindow.h"
#include "Dashboard.h"
#include "dialog/NewOrganism.h"
#include "dialog/Preferences.h"
#include "core/Application.h"
#include "settings/FileSettings.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_fileSettings = new FileSettings(this);
    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::create() {
    NewOrganism newOrganism(m_fileSettings->pathWorkDirectory());

    if (newOrganism.exec() == QDialog::Accepted) {
        m_dashboard = new Dashboard(newOrganism.name(), newOrganism.directory());
        setCentralWidget(m_dashboard);
    }
}

void MainWindow::showPreferences() {
    Preferences preferences(m_fileSettings);
    preferences.exec();
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
tr(R"(<h3>%1 %2</h3>
Artifical life unit<br><br>
Based on Qt %3<br>
Build on %4 %5<br><br>
<a href=%6>%6</a><br><br>
Copyright © %7, Vladimir Zarypov)")
        .arg(Application::Name, Application::Version, QT_VERSION_STR,
        Application::BuildDate, Application::BuildTime, Application::Url, Application::Years));
}

void MainWindow::readSettings() {
    QByteArray geometry = m_fileSettings->mainWindowGeometry();

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    restoreState(m_fileSettings->mainWindowState());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}
