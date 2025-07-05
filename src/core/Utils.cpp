#include "Utils.h"
#include <QDir>

Utils::Utils() {}

QString Utils::workDir() {
    return QDir::homePath();
}
