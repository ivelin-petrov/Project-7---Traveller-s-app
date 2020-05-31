#include "travel.h"

Travel::Travel(const std::string _destination, const std::vector<std::string> _period, 
        const std::string _comment, const std::vector<std::string> _photos , double _grade) 
        : destination(_destination), period(_period), comment(_comment), photos(_photos), grade(_grade) {}

Travel::Travel(const Travel& other) : destination(other.destination), period(other.period),
                comment(other.comment), photos(other.photos), grade(other.grade) {}

Travel& Travel::operator = (const Travel& other){
    if(this != &other)
    {
        destination = other.destination;
        period = other.period;
        comment = other.comment;
        photos = other.photos;       // std::vector<std::string>
        grade = other.grade;
    }
    return *this;
}

Travel::~Travel() {}

std::istream& operator >> (std::istream& in, Travel& other)
{
    std::cout << "Destinaion: " << std::endl;
    std::string _destination;
    std::getline(in, _destination);
    other.changeDestination(_destination);

    std::cout << "First date: " << std::endl;
    std::string dateF;
    in >> dateF;
    other.changePeriodBegin(dateF);
    
    std::cout << "Second date: " << std::endl; 
    std::string dateS;
    in >> dateS;
    other.changePeriodEnd(dateS);

    std::cout << "Comment: " << std::endl;
    std::cin.ignore();
    std::string _comment;
    std::getline(in, _comment);
    other.changeComment(_comment);
    
    int n = 0;
    std::cout << "Enter the number of pictures you want to upload." << std::endl;
    std::cin >> n;
    std::string photo;
    std::cout << "Photos: " << std::endl;
    for(size_t i = 0 ; i < n; ++i)
    {
        in >> photo;
        other.photos.push_back(photo);
    }
    std::cout << "Number of photos you want to upload: " << other.photos.size() << std::endl;

    std::cout << "Grade: " << std::endl;
    in >> other.grade;

    return in;
}

int Travel::getPhotosSize() const { return photos.size(); }

std::string Travel::getDestination() const { return destination; }
std::string Travel::getPeriodBegin() const { return period[0]; }
std::string Travel::getPeriodEnd() const { return period[1]; }
std::string Travel::getComment() const { return comment; }
std::string Travel::getPhoto(size_t i) const { return photos[i]; }
std::string& Travel::getPhoto(size_t i) { return photos[i]; }
double Travel::getGrade() const { return grade; }
std::vector<std::string>& Travel::getPhotos() { return photos; }


void Travel::changeDestination(const std::string& _destination) { destination = _destination; }
void Travel::changePeriodBegin(const std::string& _period) { period[0] = _period; }
void Travel::changePeriodEnd(const std::string& _period) { period[1] = _period; }
void Travel::changeComment(const std::string& _comment) { comment = _comment; }
void Travel::changePhoto(const std::string& _photo, size_t i) { photos[i] = _photo; }
void Travel::changeGrade(double _grade) { grade = _grade; }


bool correctDate(const std::string& date){
    bool erratic = false;                       
    std::string year = date.substr(0,4);        // YYYY-MM-DD
    std::string month = date.substr(5,2);
    std::string day = date.substr(8,2);

    int _year = std::stoi(year);                // converts string with numbers to int
    int _month = std::stoi(month);
    int _day = std::stoi(day);

    //std::cout << _year << " " << _month << " " << _day << std::endl;
    if((_year >= 0 && _year <= 2020) && (_month >= 1 && _month <= 12) && (_day >= 1 && _day <= 31)){
        erratic = true;
        if(_month == 2 && _day > 29){
            erratic = false;
        }
        if(((_year % 4 != 0) || (_year % 100 == 0)) && (_year % 400 != 0)){      // leap year
            if(_month == 2 && _day == 29){
                erratic =  false;
            }
        }
        if((_month == 4 || _month == 6 || _month == 9 || _month == 11) && _day == 31){
            erratic = false;
        }
        if(_year == 2020 && _month > 5){        // last date : 2020-05-31
            erratic = false;
        }
    }


    return erratic;
}

bool correctPeriod(const std::string& date1, const std::string& date2){
    bool erratic = false;
    if(correctDate(date1) == 1 && correctDate(date2) == 1)
    {
        std::string year1 = date1.substr(0,4);        
        std::string year2 = date2.substr(0,4);  
        int year_firstDate = std::stoi(year1);  
        int year_secondDate = std::stoi(year2);

        if(year_firstDate == year_secondDate)
        {
            std::string month1 = date1.substr(5,2);
            std::string month2 = date2.substr(5,2);
            int month_firstDate = std::stoi(month1);
            int month_secondDate = std::stoi(month2);

            if(month_firstDate == month_secondDate)
            {
                std::string day1 = date1.substr(8,2);
                std::string day2 = date2.substr(8,2);
                int day_firstDate = std::stoi(day1);
                int day_secondDate = std::stoi(day2);

                if(day_firstDate <= day_secondDate){
                    erratic = true;
                }

            }else if(month_firstDate < month_secondDate)
            {
                erratic = true;
            }

        }else if(year_firstDate < year_secondDate){
            erratic = true;
        }          
    }

    return erratic;
}

bool correctPhoto(const std::string& photo){
    bool erratic = true;
    int j = 0;
    for(int i = 0; i < photo.size(); ++i){
        if(photo[i] == '.'){
            j = i + 1;
            break;
        }
        if((photo[i] < 'a' || photo[i] > 'z') && (photo[i] < 'A' || photo[i] > 'Z') && photo[i] != '_'){
            erratic = false;
            break;
        }
    }
 
    std::string ending = photo.substr(j);
    if(erratic == true){    //jpeg png
        if(strcmp(ending.c_str(), "jpeg") != 0 && strcmp(ending.c_str(), "png") != 0)
        {
            erratic = false;
        }        
    }

    if(photo[0] == '.'){
        erratic = false;
    }

    return erratic;
}

bool correctGrade(double grade){
    bool erratic = false;
    if(grade >= 1.0 && grade <= 5.0){
        erratic = true;
    }

    return erratic;
}
