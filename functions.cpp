#include "functions.h"

bool Functions::foundInUsers_db(const std::string& _name)
{
    bool found = false;
    std::string line;
    std::ifstream ifile("users.db");
    if(ifile.good())
    {
        while(std::getline(ifile, line))
        {
            if(line == _name)
            {
                found = true;   
            }
        }
        ifile.close();
    }else{ std::cout << "Error." << std::endl; }

    return found;
}

bool Functions::foundInUsers_db(const std::string& _name, const std::string& _password)
{
    int count = 0;
    std::string line;
    std::ifstream ifile("users.db");
    if(ifile.good())
    {
        while(std::getline(ifile, line))
        {
            if(line == _name)
            {
                ++count;   
            }else if(line == _password)
            {
                ++count;
                break;
            }
        }
        ifile.close();
    }else{ std::cout << "Error." << std::endl; }

    return (count == 2);
}

bool Functions::foundInDestinations_txt(const std::string& _destination)
{
    bool found = false;
    std::string line;
    std::ifstream ilist("destinations.txt");
    if(ilist.good())
    {
        while(std::getline(ilist, line))
        {
            if(line == _destination)
            {
                found = true;
                break;
            }
        }
        ilist.close();
    }else{ std::cout << "Error." << std::endl; }

    return found;
}

void Functions::printDestinations()
{
    std::string _destination;
    std::ifstream ilist("destinations.txt");
    if(ilist.is_open())
    {
        while(std::getline(ilist, _destination)){
            std::cout << _destination << std::endl;
        }
    }else{
        std::cout << "File could not be opened." << std::endl;
    }
}

User Functions::load_user_withoutFriends(const std::string& _name)
{
    User result;

    if(foundInUsers_db(_name) == 1)
    {
        result.changeName(_name);
        result.changeTravels(load_travels(_name));

        std::string line;                       
        std::ifstream ifile("users.db");            // load mail and password
        if(ifile.good())
        {
            while(std::getline(ifile, line))
            {
                if(line == _name)
                {
                    std::getline(ifile, line);      // line = mail
                    result.changeMail(line);
                    std::getline(ifile, line);      // line = password
                    result.changePassword(line);
                }
            }
            ifile.close();
        }else{ std::cout << "Error while opening 'users.db'." << std::endl; }
        
    }else{
        std::cout << "Incorrect name" << std::endl;
    }

    return result;
}

void Functions::has_visited(const User& myUser, const std::string& _destination)
{
    size_t size = myUser.getFriendsSize();

    for(int i = 0; i < size; ++i)
    {   
        std::string name = myUser.getFriend(i);     // getFriend(i) -> string = friend's name
        User temp(load_user_withoutFriends(name));                                 

        size_t n = temp.getTravelsSize();

        for(int j = 0; j < n; ++j)
        {
            if(temp.getTravel(j).getDestination() == _destination)
            {
                std::cout << temp.getName() << " has visited '" << _destination << "'.\n";
                std::cout << "Their comment is: " << temp.getTravel(j).getComment() << std::endl;

                break;
            }
        }
        std::cout << std::endl;
    }   
}

void Functions::average_grade(const User& myUser, const std::string& _destination)
{
    double average_grade = 0;
    int counter = 0;
    size_t size = myUser.getFriendsSize();

    for(size_t i = 0; i < size; ++i)
    {
        std::string name = myUser.getFriend(i);     // getFriend(i) -> string = friend's name
        User temp(load_user_withoutFriends(name)); 
        
        size_t n = temp.getTravelsSize();

        for(size_t j = 0; j < n; ++j)
        {
            if(temp.getTravel(j).getDestination() == _destination)
            {
                std::cout << temp.getName() << " has visited '" << _destination << "'.\n";
                std::cout << "Their grade is: " << temp.getTravel(j).getGrade() << std::endl;
                average_grade += temp.getTravel(j).getGrade();

                ++counter;
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "The average grade of destination '" << _destination << "' is " << average_grade / counter << std::endl; 
}

std::vector<Travel> Functions::load_travels(const std::string& _name)
{   
    std::vector<Travel> travels;
    int i = 0;

    std::string fileName = _name + ".db";
    std::string line;
    std::ifstream ifile(fileName);
    if(ifile.good())
    {
        while(!ifile.eof())
        {
            Travel travel;

            std::getline(ifile, line);
            travel.changeDestination(line);
            ifile >> line;
            travel.changePeriodBegin(line);
            ifile >> line;
            travel.changePeriodEnd(line);
  
            std::getline(ifile, line);   // gets '\n' 
            std::getline(ifile, line);   // gets the correct string
        
            travel.changeComment(line);
            
            int n;
            ifile >> n;

            for(size_t i = 0; i < n; ++i)
            {
                ifile >> line;
                travel.getPhotos().resize(n);
                travel.changePhoto(line, i);
            }

            double _grade;
            ifile >> _grade;
            travel.changeGrade(_grade);
            ++i;

            travels.resize(i - 1);
            travels.push_back(travel);

            std::getline(ifile, line);   // gets '\n' 
        }
         
    }else{
        std::cout << "Error." << std::endl;
    }
    travels.pop_back(); // removes the last element which is empty

    return travels;
}

User Functions::load_user(const std::string& _name)
{
    User result;

    if(foundInUsers_db(_name) == 1)
    {
        result.changeName(_name);                   // load name
        result.changeTravels(load_travels(_name));  // load travels

        std::string line;                       
        std::ifstream ifile("users.db");            // load mail and password
        if(ifile.good())
        {
            while(std::getline(ifile, line))
            {
                if(line == _name)
                {
                    std::getline(ifile, line);      // line = mail
                    result.changeMail(line);
                    std::getline(ifile, line);      // line = password
                    result.changePassword(line);
                }
            }
            ifile.close();
        }else{ std::cout << "Error while opening 'users.db'." << std::endl; }

        std::cout << std::endl;
        std::cout << "Now, it is time for you to add all your friends by writing down their names." << std::endl;
        std::cout << "How many friends do you have? Enter a number." << std::endl;
        size_t n;
        std::cin >> n;
        std::cin.ignore();

        if(n == 0){
            std::cout << "So sad ..." << std::endl;
        }
        else{

            std::cout << "Now enter their names one by one." << std::endl;

            std::string name_of_a_friend;

            std::vector<std::string> friendsNew;
            friendsNew.resize(n);
            int k = 0;
            for(size_t i = 0; i < n; ++i)
            {
                std::getline(std::cin, name_of_a_friend);
                if(foundInUsers_db(name_of_a_friend) == 0)
                {
                    std::cout << "The person is not registered yet." << std::endl;
                }
                else if(foundInUsers_db(name_of_a_friend) == 1){
                    friendsNew[k] = name_of_a_friend;
                    ++k;
                }
            }
            result.changeFriends(friendsNew);
            result.resizeFriends(k);
        }
    }else{
        std::cout << "Incorrect name" << std::endl;
    }

    return result;
}

void Functions::new_travel(const std::string& name)
{
    Travel travel;
    std::cin >> travel;

    std::ofstream olist("destinations.txt", std::ios::app);
    if(foundInDestinations_txt(travel.getDestination()) == 0)
    {
        if(olist.is_open())
        {
            olist << travel.getDestination() << std::endl;
        }else{
            std::cout << "File could not be opened." << std::endl;
        }
    }
    olist.close();

    if(correctPeriod(travel.getPeriodBegin(), travel.getPeriodEnd()) == 1 && correctGrade(travel.getGrade()) == 1)
    {
        bool correct = true;
        for(size_t i = 0; i < travel.getPhotosSize(); ++i)
        {
            if(correctPhoto(travel.getPhoto(i)) == 0)
            {
                correct = false;
                break;
            }
        }
        if(correct == true)
        {
            std::string file_user = name + ".db";
            std::ofstream ofile_user(file_user, std::ios::app);
            if(ofile_user.is_open())
            {
                ofile_user << travel.getDestination() << std::endl;
                ofile_user << travel.getPeriodBegin() << " ";
                ofile_user << travel.getPeriodEnd() << std::endl;
                ofile_user << travel.getComment() << std::endl;

                ofile_user << travel.getPhotosSize() << " ";
                for(size_t j = 0; j < travel.getPhotosSize(); ++j)
                {
                    ofile_user << travel.getPhoto(j) << " ";
                }
                ofile_user << std::endl;
                ofile_user << travel.getGrade() << std::endl;

                ofile_user.close();
            }else{
                std::cout << "File could not be opened." << std::endl;
            }
        }else{
            std::cout << "Wrong photo name. Couldn't complete the addition of a new travel." << std::endl;
        }
    }else{
        std::cout << "Wrong period and/or grade. Couldn't complete the addition of a new travel." << std::endl;
    }
}

void Functions::options(const std::string& name)
{
    std::cout << "Welcome. You have successfully entered your account. Choose a command: " << std::endl;
    std::cout << std::endl;
    std::cout << "1) add new travel" << std::endl;
    std::cout << "2) check if your friends have visited a certain destination and their comments about it" << std::endl;
    std::cout << "3) check the grade that your friends have given for a certain destination and the average grade of this destination" << std::endl;
    std::cout << "4) print the list of all destinations" << std::endl;
    std::cout << std::endl;
    std::cout << "Write down 'new travel' for 1) / 'has visited' for 2) / 'average grade' for 3) / 'list of destinations' for 4)" << std::endl;

    std::string choice;
    std::getline(std::cin, choice);
    
    if(strcmp(choice.c_str(), "new travel") == 0)
    {
        new_travel(name);
    }
    else if(strcmp(choice.c_str(), "has visited") == 0)
    {
        User myUser(load_user(name));

        std::cout << std::endl;
        std::cout << "Destination you want to check." << std::endl;

        std::string destination;
        std::getline(std::cin, destination);

        if(foundInDestinations_txt(destination) == 1){
            std::cout << std::endl;
            has_visited(myUser, destination);
        }
        else{
            std::cout << "Not a valid destination, sorry..." << std::endl;
        }
    }
    else if(strcmp(choice.c_str(), "average grade") == 0)
    {
        User myUser(load_user(name));

        std::cout << std::endl;
        std::cout << "Destination you want to check." << std::endl;

        std::string destination;
        std::getline(std::cin, destination);

        std::cout << std::endl;
        average_grade(myUser, destination);
    }
    else if(strcmp(choice.c_str(), "list of destinations") == 0)
    {
        std::cout << std::endl;
        printDestinations();
    }
    else{ std::cout << "Exiting..." << std::endl; }
}

void Functions::registration()
{       
    std::string name;
    std::string mail;
    std::string password;

    std::cout << "Enter name:" << std::endl;
    std::getline(std::cin, name);

    std::cout << "Enter mail:" << std::endl;
    std::getline(std::cin, mail);

    std::cout << "Enter password" << std::endl;
    std::getline(std::cin, password); 

    if(foundInUsers_db(name) == 0)
    {   
        std::ofstream ofile("users.db", std::ios::app);
        if(ofile.is_open())
        {
            ofile << name << std::endl;
            ofile << mail << std::endl;
            ofile << password << std::endl;
            ofile.close();
        }
    }
    else{
        std::cout << "Name already taken." << std::endl;
    }

    // създава се личн база данни
    std::string file_user = name + ".db";
    std::ofstream ofile_user(file_user, std::ios::app);
}

void Functions::login()
{
    std::string name;
    std::string password;

    std::string line;

    std::cout << "Enter name:" << std::endl;
    std::getline(std::cin, name);

    std::cout << "Enter password:" << std::endl;
    std::getline(std::cin, password);

    if(foundInUsers_db(name, password) == 1)
    {
        std::cout << std::endl;
        std::cout << "Logging in account..." << std::endl;

        options(name);

    }else{
        std::cout << "Name and/or password incorrect." << std::endl;
    }
}