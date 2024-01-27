#include "Application.h"
#include <QSettings>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setApplicationVersion(version());
    QSettings::setDefaultFormat(QSettings::IniFormat);
}
