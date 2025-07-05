#include "NewOrganism.h"
#include "ui/widget/BrowseLayout.h"
#include "core/Utils.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>

NewOrganism::NewOrganism() {
    setWindowTitle(tr("New Organism"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewOrganism::setOkButtonState);

    m_directoryBrowseLayout = new BrowseLayout;
    m_directoryBrowseLayout->lineEdit()->setText(Utils::workDir());
    connect(m_directoryBrowseLayout->lineEdit(), &QLineEdit::textChanged, this, &NewOrganism::setOkButtonState);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Directory:"), m_directoryBrowseLayout);

    setContentLayout(formLayout);

    resizeToWidth(500);
    m_nameLineEdit->setFocus();
    setOkButtonState();
}

QString NewOrganism::name() const {
    return m_nameLineEdit->text();
}

QString NewOrganism::directory() const {
    return m_directoryBrowseLayout->lineEdit()->text();
}

void NewOrganism::accept() {
    if (QDir().exists(directory() + "/" + name())) {
        QMessageBox::critical(this, QString(), tr("World already exists!"));
    } else {
        StandardDialog::accept();
    }
}

void NewOrganism::setOkButtonState() {
    bool isAllFieldsFilled = !(m_nameLineEdit->text().isEmpty() || m_directoryBrowseLayout->lineEdit()->text().isEmpty());
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(isAllFieldsFilled);
}
