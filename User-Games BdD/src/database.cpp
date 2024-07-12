#include "database.h"
#include <iostream>

Database::Database(const char *filename)
{
    if (sqlite3_open(filename, &db))
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

Database::~Database()
{
    sqlite3_close(db);
}

void Database::executeSQL(const char *sql)
{
    char *errorMessage;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

sqlite3 *Database::getDB()
{
    return db;
}

void Database::createTables()
{
    const char *createUsersTable = "CREATE TABLE IF NOT EXISTS Users ("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "Name TEXT NOT NULL, "
                                   "Email TEXT NOT NULL UNIQUE);";
    executeSQL(createUsersTable);

    const char *createGamesTable = "CREATE TABLE IF NOT EXISTS Games ("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "Name TEXT NOT NULL UNIQUE, "
                                   "Genre TEXT NOT NULL);";
    executeSQL(createGamesTable);

    const char *createPurchasesTable = "CREATE TABLE IF NOT EXISTS Purchases ("
                                       "UserID INTEGER, "
                                       "GameID INTEGER, "
                                       "FOREIGN KEY(UserID) REFERENCES Users(ID), "
                                       "FOREIGN KEY(GameID) REFERENCES Games(ID), "
                                       "PRIMARY KEY(UserID, GameID));";
    executeSQL(createPurchasesTable);

    std::cout << "Database setup completed." << std::endl;
}