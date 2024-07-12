#ifndef USER_H
#define USER_H

#include "database.h"
#include <string>

class User
{
private:
    int id;
    std::string name;
    std::string email;

public:
    User(int id, std::string name, std::string email);
};

#endif
