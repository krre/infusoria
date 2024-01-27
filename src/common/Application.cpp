#include "Application.h"
#include <QSettings>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setApplicationVersion(version());

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif
}
