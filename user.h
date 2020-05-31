#ifndef USER_H__
#define USER_H__

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "travel.h"


class User{
  private:
    std::vector<Travel> travels;
    std::vector<std::string> friends;
    std::string name;
    std::string mail;
    std::string password;

  public:
    User(const std::vector<Travel> _travels = {}, const std::vector<std::string> _friends = {},
        const std::string _name = "Unknown", const std::string _mail = "Unknown", const std::string _password = "Unknown");
    User(const User& other);
    User& operator = (const User& other);
    ~User();

    bool operator == (const User& other);
    
    std::string getName() const;
    std::string getMail() const;
    std::string getPassword() const;

    Travel getTravel(int i) const;
    Travel& getTravel(int i);
    size_t getTravelsSize() const;

    std::string getFriend(int i) const;
    std::string& getFriend(int i);
    size_t getFriendsSize() const;

    void resizeFriends(int size);

    void changeName(const std::string& _name);
    void changeMail(const std::string& _mail);
    void changePassword(const std::string& _password);
    void changeTravels(const std::vector<Travel>& _travels);
    void changeFriends(const std::vector<std::string>& _friends);

    void addTravel(const Travel& other);
    void addFriend(const std::string& name_of_a_friend);
};

#endif