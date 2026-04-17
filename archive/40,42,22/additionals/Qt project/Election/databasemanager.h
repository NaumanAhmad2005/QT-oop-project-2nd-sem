#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance();           // Singleton access
    QSqlDatabase getDatabase();                   // Get DB reference
    bool connect();                               // Connect to DB

private:
    DatabaseManager();                            // Private constructor
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H



// references :
// GeekforGeeks
// stack Overflow
