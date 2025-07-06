#include "Utils.h"
#include <QStandardPaths>

Utils::Utils() {}

QString Utils::workDir() {
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}
