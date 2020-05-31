#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "functions.h"


TEST_CASE("Correct Photo")
{
    std::string photo1 = "sunset_on_the_coast.jpeg";
    CHECK(correctPhoto(photo1) == 1);
    
    std::string photo2 = "shores.png";
    CHECK(correctPhoto(photo2) == 1);

    std::string photo3 = "the_mountain_and_beyond.jpeg";
    CHECK(correctPhoto(photo3) == 1);

    std::string photo4 = "city council.png";
    CHECK(correctPhoto(photo4) == 0);

    std::string photo5 = "_Magnificent_View_.jpeg";
    CHECK(correctPhoto(photo5) == 1);

    std::string photo6 = "The_37th_anniversary.png";
    CHECK(correctPhoto(photo6) == 0);

    std::string photo7 = "my_20th_birthday.jpeg";
    CHECK(correctPhoto(photo7) == 0);

    std::string photo8 = ".jpeg";
    CHECK(correctPhoto(photo8) == 0);

    std::string photo9 = "_on_journey_.png";
    CHECK(correctPhoto(photo9) == 1);

    std::string photo10 = "reunion.jpeg.png";
    CHECK(correctPhoto(photo10) == 0);

    std::string photo11 = "concrete_texture..jpeg";
    CHECK(correctPhoto(photo11) == 0);

    std::string photo12 = "mosaic_tiles_texture.pdf";
    CHECK(correctPhoto(photo12) == 0);
    
    std::string photo13 = "mosaic_tiles_texture.jpg";
    CHECK(correctPhoto(photo13) == 0);
}

TEST_CASE("Correct Date & Period")
{
    std::string date1 = "2020-02-29";   // YYYY-MM-DD
    CHECK(correctDate(date1) == 1);

    std::string date2 = "2019-02-29";
    CHECK(correctDate(date2) == 0);

    std::string date3 = "2020-06-01";   // last correct date -> 2020-05-31
    CHECK(correctDate(date3) == 0);

    std::string date4 = "2020-05-31";
    CHECK(correctDate(date4) == 1);

    std::string date5 = "0000-01-31";
    CHECK(correctDate(date5) == 1);

    std::string date6 = "2000-02-29";
    CHECK(correctDate(date6) == 1);

    std::string date7 = "2019-06-31";
    CHECK(correctDate(date7) == 0);

    std::string date8 = "2017-07-31";
    CHECK(correctDate(date8) == 1);

    std::string date9 = "2014-11-31";
    CHECK(correctDate(date9) == 0);

    std::string date10 = "2019-07-11";
    CHECK(correctDate(date10) == 1);

    std::string date11 = "2019-08-10";
    CHECK(correctDate(date11) == 1);

    std::string date12 = "2019-13-10";
    CHECK(correctDate(date12) == 0);

    std::string date13 = "2019-03-32";
    CHECK(correctDate(date13) == 0);

    std::string date14 = "2019-04-31";
    CHECK(correctDate(date14) == 0);

    CHECK(correctPeriod(date2, date4) == 0);    // 2019-02-29 -> 2020-05-31
    CHECK(correctPeriod(date10, date11) == 1);  // 2019-07-11 -> 2019-08-10
    CHECK(correctPeriod(date11, date10) == 0);  // 2019-08-10 -> 2019-07-11
    CHECK(correctPeriod(date11, date11) == 1);  // 2019-08-10 the same date
    CHECK(correctPeriod(date4, date3) == 0);    // 2020-05-31 -> 2020-06-01   the last correct date is 2020-05-31
    CHECK(correctPeriod(date1, date4) == 1);    // 2020-02-29 -> 2020-05-31
    CHECK(correctPeriod(date4, date1) == 0);    // 2020-05-31 -> 2020-02-29 
}

TEST_CASE("Correct Date")
{
    double grade1 = 0.9;
    CHECK(correctGrade(grade1) == 0);

    double grade2 = 5.1;
    CHECK(correctGrade(grade2) == 0);

    double grade3 = 1;
    CHECK(correctGrade(grade3) == 1);

    double grade4 = 5;
    CHECK(correctGrade(grade4) == 1);

    double grade5 = 3.7;
    CHECK(correctGrade(grade5) == 1);
}

TEST_CASE("Travel constructor")
{
    Travel travel1("Burgas, Bulgaria", {"2019-03-17", "2019-03-29"}, "Very beautiful city on the Black Sea coast. I spent two unforgettable weeks there meeting new people.", 
              {"photo_of_hotel.jpeg", "photo_of_sea.jpeg", "my_new_friends.jpeg"}, 5);

    CHECK(correctPeriod(travel1.getPeriodBegin(), travel1.getPeriodEnd()) == 1);
    CHECK(correctGrade(travel1.getGrade()) == 1);
    CHECK(correctPhoto(travel1.getPhoto(0)) == 1);
    CHECK(correctPhoto(travel1.getPhoto(1)) == 1);
    CHECK(correctPhoto(travel1.getPhoto(2)) == 1);
}

TEST_CASE("Testing load_travels(_name)")
{
    User user;
    user.changeName("Joe");
    CHECK(strcmp(user.getName().c_str(), "Joe") == 0);
    
    user.changeTravels(Functions::load_travels("Joe"));
    CHECK(strcmp(user.getTravel(0).getPhoto(2).c_str(), "city_square.jpeg") == 0);
    CHECK(strcmp(user.getTravel(1).getPeriodEnd().c_str(), "2020-04-23") == 0);
    CHECK(strcmp(user.getTravel(2).getPhoto(1).c_str(), "beach.png") == 0);
    CHECK(strcmp(user.getTravel(3).getComment().c_str(), "Winter wonder.") == 0);
    CHECK(user.getTravel(3).getGrade() == 4.3);
}

TEST_CASE("Testing load_user(_name)")
{
    User user = Functions::load_user_withoutFriends("Jack Black");  // user1
    CHECK(user.getMail() == "blackjack@gmail.com");
    CHECK(user.getPassword() == "97943");
    CHECK(user.getTravelsSize() == 2);

    Travel travel = user.getTravel(1);
    CHECK(travel.getDestination() == "Plovdiv, Bulgaria");
    CHECK(travel.getGrade() == 4.4);

    User user2 = Functions::load_user_withoutFriends("Joe");        // user2     
    CHECK(user2.getMail() == "joe@abv.bg");
    CHECK(user2.getPassword() == "57683");
    CHECK(user2.getTravelsSize() == 4);

    Travel travel2 = user2.getTravel(3);
    CHECK(travel2.getDestination() == "Lovech, Bulgaria");
    CHECK(travel2.getGrade() == 4.3);

    User user3 = Functions::Functions::load_user_withoutFriends("John Travolta");   // user3
    CHECK(user3.getMail() == "travoltajohn@gmail.com");
    CHECK(user3.getPassword() == "34987");
    CHECK(user3.getTravelsSize() == 1);

    Travel travel3 = user3.getTravel(0);
    CHECK(travel3.getDestination() == "Lovech, Bulgaria");
    CHECK(travel3.getGrade() == 3.9);
}

int main()
{
    // g++ main.cpp travel.cpp user.cpp functions.cpp -o main.exe 


    // пускане на тестовете
    doctest::Context().run();


    
    std::string command;

    std::cout << "Write down 'registration' or 'login'. To shut down the program - 'exit'." << std::endl;
    std::getline(std::cin, command);
    
    if(strcmp(command.c_str(), "registration") == 0)      // to convert string to const char*
    {
        Functions::registration();
    }
    else if(strcmp(command.c_str(), "login") == 0)
    {
        Functions::login();
    }
    else if(command == "exit")                            // compares string and const char* (operator ==)
    {
        std::cout << "Exiting program..." << std::endl;
    }else{
        std::cout << "Incorrectly written command." << std::endl;
    }
    

    return 0;
}