#include "SqliteDatabaseHandler.h"
#include <iostream>

void createTables(SqliteDatabaseHandler &dbHandler)
{
    dbHandler.prepareQuery(
        "CREATE TABLE IF NOT EXISTS Users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL)");
    dbHandler.execute();

    dbHandler.prepareQuery(
        "CREATE TABLE IF NOT EXISTS Games ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE NOT NULL, "
        "genre TEXT NOT NULL)");
    dbHandler.execute();

    dbHandler.prepareQuery(
        "CREATE TABLE IF NOT EXISTS UserGame ("
        "user_id INTEGER, "
        "game_id INTEGER, "
        "FOREIGN KEY (user_id) REFERENCES Users(id), "
        "FOREIGN KEY (game_id) REFERENCES Games(id), "
        "PRIMARY KEY (user_id, game_id))");
    dbHandler.execute();
}

void addUser(SqliteDatabaseHandler &dbHandler, const std::string &name, const std::string &email)
{
    dbHandler.prepareQuery("INSERT INTO Users (name, email) VALUES (?, ?)");
    dbHandler.addParameter(1, name);
    dbHandler.addParameter(2, email);
    dbHandler.execute();
}

void listUsers(SqliteDatabaseHandler &dbHandler)
{
    dbHandler.prepareQuery("SELECT * FROM Users");
    auto users = dbHandler.fetchAll();

    for (const auto &row : users)
    {
        std::cout << "ID: " << row.at("id") << ", Name: " << row.at("name") << ", Email: " << row.at("email") << std::endl;
    }
}

void addGame(SqliteDatabaseHandler &dbHandler, const std::string &name, const std::string &genre)
{
    dbHandler.prepareQuery("INSERT INTO Games (name, genre) VALUES (?, ?)");
    dbHandler.add
