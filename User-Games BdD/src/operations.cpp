#include "operations.h"
#include <iostream>

void addUser(Database &db, const std::string &name, const std::string &email)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Users (Name, Email) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void addGame(Database &db, const std::string &name, const std::string &genre)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Games (Name, Genre) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, genre.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void deleteUser(Database &db, int userID)
{
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM Users WHERE ID = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, userID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void deleteGame(Database &db, int gameID)
{
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM Games WHERE ID = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, gameID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void updateUser(Database &db, int userID, const std::string &name, const std::string &email)
{
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Users SET Name = ?, Email = ? WHERE ID = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, userID);

    int result = sqlite3_step(stmt);
    if (result == SQLITE_DONE)
    {
        // Verificar si se actualizó alguna fila
        if (sqlite3_changes(db.getDB()) > 0)
        {
            std::cout << "Usuario con ID " << userID << " modificado correctamente." << std::endl;
        }
        else
        {
            std::cerr << "Error: No existe usuario con ID " << userID << "." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void updateGame(Database &db, int gameID, const std::string &name, const std::string &genre)
{
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Games SET Name = ?, Genre = ? WHERE ID = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, gameID);

    int result = sqlite3_step(stmt);
    if (result == SQLITE_DONE)
    {
        // Verificar si se actualizó alguna fila
        if (sqlite3_changes(db.getDB()) > 0)
        {
            std::cout << "Juego con ID " << gameID << " modificado correctamente." << std::endl;
        }
        else
        {
            std::cerr << "Error: No existe juego con ID " << gameID << "." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void searchUser(Database &db, const std::string &email)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Users WHERE Email = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *email = sqlite3_column_text(stmt, 2);
        std::cout << "ID: " << id << ", Name: " << name << ", Email: " << email << std::endl;
    }
    else
    {
        std::cout << "Usuario con correo electrónico '" << email << "' no encontrado." << std::endl;
    }
    sqlite3_finalize(stmt);
}

void searchGame(Database &db, const std::string &name)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Games WHERE Name = ?;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *genre = sqlite3_column_text(stmt, 2);
        std::cout << "ID: " << id << ", Name: " << name << ", Genre: " << genre << std::endl;
    }
    else
    {
        std::cout << "Juego con nombre '" << name << "' no encontrado." << std::endl;
    }
    sqlite3_finalize(stmt);
}

void listUsers(Database &db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Users;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }

    std::cout << "=== Lista de Usuarios ===" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *email = sqlite3_column_text(stmt, 2);
        std::cout << "ID: " << id << ", Nombre: " << name << ", Email: " << email << std::endl;
    }
    sqlite3_finalize(stmt);
}

void listGames(Database &db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Games;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }

    std::cout << "=== Lista de Juegos ===" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *genre = sqlite3_column_text(stmt, 2);
        std::cout << "ID: " << id << ", Nombre: " << name << ", Género: " << genre << std::endl;
    }
    sqlite3_finalize(stmt);
}

void purchaseGame(Database &db, int userID, int gameID)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Purchases (UserID, GameID) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, userID);
    sqlite3_bind_int(stmt, 2, gameID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void showPurchases(Database &db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT Users.Name, Games.Name "
                      "FROM Purchases "
                      "JOIN Users ON Purchases.UserID = Users.ID "
                      "JOIN Games ON Purchases.GameID = Games.ID;";
    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *userName = sqlite3_column_text(stmt, 0);
        const unsigned char *gameName = sqlite3_column_text(stmt, 1);
        std::cout << "User: " << userName << ", Game: " << gameName << std::endl;
    }
    sqlite3_finalize(stmt);
}