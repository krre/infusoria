#pragma once
#include "StandardDialog.h"

class Settings;
class QLineEdit;

class Preferences : public StandardDialog {
    Q_OBJECT
public:
    Preferences(Settings* settings);

public slots:
    void accept() override;

private:
    void readSettings();
    void writeSettings();

    Settings* m_settings = nullptr;
    QLineEdit* m_workDirLineEdit = nullptr;
};
