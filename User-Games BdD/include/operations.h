#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "database.h"
#include <string>

void addUser(Database &db, const std::string &name, const std::string &email);
void deleteUser(Database &db, int userID);
void updateUser(Database &db, int userID, const std::string &name, const std::string &email);
void searchUser(Database &db, const std::string &email);
void listUsers(Database &db);

void addGame(Database &db, const std::string &name, const std::string &genre);
void deleteGame(Database &db, int gameID);
void updateGame(Database &db, int gameID, const std::string &name, const std::string &genre);
void searchGame(Database &db, const std::string &name);
void listGames(Database &db);

void purchaseGame(Database &db, int userID, int gameID);
void showPurchases(Database &db);

#endif // OPERATIONS_H
