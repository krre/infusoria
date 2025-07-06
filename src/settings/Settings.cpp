#include "Settings.h"
#include "core/Utils.h"

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
}

namespace Path {
    constexpr auto WorkDirectory = "Path/workDirectory";
}

void Settings::setMainWindowGeometry(const QByteArray& geometry) {
    setValue(MainWindow::Geometry, geometry);
}

QByteArray Settings::mainWindowGeometry() const {
    return value(MainWindow::Geometry).toByteArray();
}

void Settings::setMainWindowState(const QByteArray& state) {
    setValue(MainWindow::State, state);
}

QByteArray Settings::mainWindowState() const {
    return value(MainWindow::State).toByteArray();
}

void Settings::setPathWorkDirectory(const QString& workDirectory) {
    setValue(Path::WorkDirectory, workDirectory);
}

QString Settings::pathWorkDirectory() const {
    return value(Path::WorkDirectory, Utils::workDir()).toString();
}
