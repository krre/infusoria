#include "Application.h"

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Name);
    setApplicationName(Name);
    setApplicationVersion(Version);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif
}
