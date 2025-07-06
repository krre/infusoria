#include "Preferences.h"
#include "ui/widget/BrowseLayout.h"
#include "settings/Settings.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>

Preferences::Preferences(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto workDirLayout = new BrowseLayout(settings->pathWorkDirectory());
    m_workDirLineEdit = workDirLayout->lineEdit();

    auto pathLayout = new QFormLayout;
    pathLayout->addRow(tr("Work directory:"), workDirLayout);

    auto pathGroupBox = new QGroupBox(tr("Path"));
    pathGroupBox->setLayout(pathLayout);

    setContentWidget(pathGroupBox);

    resizeToWidth(500);
    readSettings();
}

void Preferences::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Preferences::readSettings() {
}

void Preferences::writeSettings() {
    m_settings->setPathWorkDirectory(m_workDirLineEdit->text());
}
