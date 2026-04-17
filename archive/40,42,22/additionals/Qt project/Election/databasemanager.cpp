#include "databasemanager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("project.db");
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}

bool DatabaseManager::connect() {
    if (!db.isOpen() && !db.open()) {
        qDebug() << "DB Connection Failed:" << db.lastError();
        return false;
    }

    // Optional: create tables here if needed
    return true;
}
