#pragma once
#include <QHBoxLayout>

class QLineEdit;

class BrowseLayout : public QHBoxLayout {
public:
    BrowseLayout(const QString& dir = QString());
    QLineEdit* lineEdit() const;

private slots:
    void onClicked();

private:
    QLineEdit* m_lineEdit = nullptr;
};
