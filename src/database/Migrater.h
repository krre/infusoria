#pragma once
#include <QHash>

class Database;

class Migrater {
public:
    Migrater(Database* db);
    void run() const;

private:
    void migration1() const; // 09.07.2025

    Database* m_db = nullptr;
    QHash<int, std::function<void()>> migrations;
};
