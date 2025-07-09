#include "Migrater.h"
#include "Database.h"
#include <QSqlQuery>

constexpr auto CurrentVersion = 1;

Migrater::Migrater(Database* db) : m_db(db) {
    migrations[1] = [this] { migration1(); };
}

void Migrater::run() const {
    int version = m_db->metaValue("version").toInt();

    if (version == CurrentVersion) return;

    for (int i = version + 1; i <= CurrentVersion; ++i) {
        migrations[i]();
        qInfo() << "Run database migration:" << i;
    }

    m_db->updateMetaValue("version", CurrentVersion);
}

void Migrater::migration1() const {
    m_db->exec(R"(
        CREATE TABLE meta(
            version INTEGER,
            name TEXT
        ))"
    );

    m_db->exec("INSERT INTO meta (version, name) VALUES (1, '')");
}
