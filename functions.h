#ifndef FUNCTIONS_H__
#define FUNCTIONS_H__

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

#include "travel.h"
#include "user.h"

class Functions{
  public:
    static bool foundInUsers_db(const std::string& _name);
    static bool foundInUsers_db(const std::string& _name, const std::string& _password);
    static bool foundInDestinations_txt(const std::string& _destination);
    static void printDestinations();

    static std::vector<Travel> load_travels(const std::string& _name);
    static User load_user_withoutFriends(const std::string& _name);
    static User load_user(const std::string& _name);

    static void new_travel(const std::string& name);
    static void has_visited(const User& myUser, const std::string& _destination);
    static void average_grade(const User& myUser, const std::string& _destination);

    static void options(const std::string& name);

    static void registration();
    static void login();
};

#endif