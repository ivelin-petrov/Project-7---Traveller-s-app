#include "user.h"

// ========== User ========== 

User::User(const std::vector<Travel> _travels, const std::vector<std::string> _friends,
    const std::string _name, const std::string _mail, const std::string _password) 
        : travels(_travels), friends(_friends), name(_name), mail(_mail), password(_password) {}
    
User::User(const User& other) : travels(other.travels), friends(other.friends), 
                                name(other.name), mail(other.mail), password(other.password) {}

User& User::operator = (const User& other){
    if(this != &other){
        travels = other.travels;
        friends = other.friends;
        name = other.name;
        mail = other.mail;
        password = other.password;
    }
    return *this;
}

User::~User() {}

bool User::operator == (const User& other){
    return (name == other.name && password == other.password && mail == other.mail);
}

std::string User::getName() const { return name; }
std::string User::getMail() const { return mail; }
std::string User::getPassword() const { return password; }

Travel User::getTravel(int i) const { return travels[i]; }
Travel& User::getTravel(int i){ return travels[i]; }
size_t User::getTravelsSize() const { return travels.size(); }

std::string User::getFriend(int i) const { return friends[i]; }
std::string& User::getFriend(int i){ return friends[i]; }
size_t User::getFriendsSize() const { return friends.size(); }

void User::resizeFriends(int size){ friends.resize(size); }

void User::changeName(const std::string& _name){ name = _name; }
void User::changeMail(const std::string& _mail){ mail = _mail; }
void User::changePassword(const std::string& _password){ password = _password; }
void User::changeTravels(const std::vector<Travel>& _travels){ travels = _travels; }
void User::changeFriends(const std::vector<std::string>& _friends){ friends = _friends; }

void User::addTravel(const Travel& other)
{
    travels.push_back(other);
}

void User::addFriend(const std::string& name_of_a_friend)
{
    friends.push_back(name_of_a_friend);
}