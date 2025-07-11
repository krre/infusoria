#include "MainWindow.h"
#include "Dashboard.h"
#include "RecentFilesMenu.h"
#include "dialog/NewOrganism.h"
#include "dialog/Preferences.h"
#include "core/Application.h"
#include "settings/FileSettings.h"
#include "organism/Organism.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QSettings>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_fileSettings = new FileSettings(this);
    changeWindowTitle();
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
        closeFile();
        m_dashboard = new Dashboard(newOrganism.name(), newOrganism.directory());
        setCentralWidget(m_dashboard);
        m_recentFilesMenu->addPath(m_dashboard->organism()->filePath());
        emit fileOpenChanged(true);
        changeWindowTitle();
    }
}

void MainWindow::open() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Organism"), m_fileSettings->pathWorkDirectory(),
                                                    tr("All Files (*);;Database Files (*.db)"));
    openFile(filePath);
}

void MainWindow::openFile(const QString& filePath) {
    closeFile();

    if (filePath.isEmpty()) return;
    if (!QFile::exists(filePath)) return;

    m_dashboard = new Dashboard(filePath);
    setCentralWidget(m_dashboard);
    m_recentFilesMenu->addPath(filePath);
    emit fileOpenChanged(true);
    changeWindowTitle();
}

void MainWindow::closeFile() {
    setCentralWidget(nullptr);

    delete m_dashboard;
    m_dashboard = nullptr;

    emit fileOpenChanged(false);
    changeWindowTitle();
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
    openFile(m_fileSettings->mainWindowLastFile());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
    m_fileSettings->setMainWindowLastFile(m_dashboard->organism()->filePath());

    m_fileSettings->setRecentFiles(m_recentFilesMenu->recentFiles());
}

void MainWindow::changeWindowTitle() {
    QString title = Application::applicationName();

    if (m_dashboard) {
        title = m_dashboard->organism()->name() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);

    m_recentFilesMenu = new RecentFilesMenu(m_fileSettings->recentFiles(), this);
    connect(m_recentFilesMenu, &RecentFilesMenu::activated, this, &MainWindow::openFile);
    fileMenu->addAction(m_recentFilesMenu->menuAction());

    auto closeAction = fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::closeFile);
    closeAction->setEnabled(false);
    connect(this, &MainWindow::fileOpenChanged, closeAction, &QAction::setEnabled);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}
