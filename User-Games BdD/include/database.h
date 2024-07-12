#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database
{
private:
    sqlite3 *db;

public:
    Database(const char *filename);
    ~Database();
    void executeSQL(const char *sql);
    sqlite3 *getDB();
    void createTables();
};

#endif
