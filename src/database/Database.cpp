#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>

Database::Database(QObject* parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

Database::~Database() {
    close();
}

void Database::create(const QString& filepath) {
    qInfo().noquote() << "Create database:" << filepath;
    m_db.close();
    m_db.setDatabaseName(filepath);

    if (!m_db.open()) {
        throw std::runtime_error(m_db.lastError().text().toStdString());
    }
}

void Database::open(const QString& filepath) {
    qInfo().noquote() << "Open database:" << filepath;
    m_db.setDatabaseName(filepath);

    if (!m_db.open()) {
        throw std::runtime_error(m_db.lastError().text().toStdString());
    }
}

void Database::close() {
    if (m_db.isOpen()) {
        qInfo().noquote() << "Close database:" << m_db.databaseName();
        m_db.close();
    }
}

bool Database::isOpen() const {
    return m_db.isOpen();
}

QSqlQuery Database::exec(const QString& sql, const QVariantMap& params) const {
    QSqlQuery query;
    query.prepare(sql);

    for (auto [key, value] : params.asKeyValueRange()) {
        query.bindValue(":" + key, value);
    }

    if (!query.exec()) {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}
