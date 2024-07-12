#ifndef GAME_H
#define GAME_H

#include "database.h"
#include <string>

class Game
{
private:
    int id;
    std::string name;
    std::string genre;

public:
    Game(int id, std::string name, std::string genre);
};

#endif
