#ifndef TRAVEL_H__
#define TRAVEL_H__

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

class Travel{ 
  private:
    std::string destination;
    std::vector<std::string> period;
    std::string comment;
    std::vector<std::string> photos;
    double grade;

  public:
    Travel(const std::string _destination = "Unknown", const std::vector<std::string> _period = {"Unknown", "Unknown"},
                const std::string _comment = "Unknown",
                const std::vector<std::string> _photos = {}, double _grade = 0);

    Travel(const Travel& other);
    Travel& operator = (const Travel& other);
    ~Travel();

    friend std::istream& operator >> (std::istream& in, Travel& other);

    int getPhotosSize() const;

    std::string getDestination() const;
    std::string getPeriodBegin() const;
    std::string getPeriodEnd() const;
    std::string getComment() const;
    std::string getPhoto(size_t i) const;
    std::string& getPhoto(size_t i);
    double getGrade() const;
    std::vector<std::string>& getPhotos();

    void changeDestination(const std::string& _destination);
    void changePeriodBegin(const std::string& _period);
    void changePeriodEnd(const std::string& _period);
    void changeComment(const std::string& _comment);
    void changePhoto(const std::string& _photo, size_t i);
    void changeGrade(double _grade);

};

bool correctDate(const std::string& date);
bool correctPeriod(const std::string& date1, const std::string& date2);
bool correctPhoto(const std::string& photo);
bool correctGrade(double grade);

#endif