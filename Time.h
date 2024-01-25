#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
public:
    Time();
    Time(int const h, int const m, int const s);
    Time(std::string const& time_string);

    std::string to_string(bool us = false) const;
    //std::string to_string(bool us) const;
    bool is_am() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);


    bool operator<(Time const& rhs) const;
    bool operator>(Time const& rhs) const;
    bool operator<=(Time const& rhs) const;
    bool operator>=(Time const& rhs) const;
    bool operator==(Time const& rhs) const;
    bool operator!=(Time const& rhs) const;

private:

    int hour {};
    int minute {};
    int second {}; 

    std::string time_string{""}; 

};

std::ostream& operator<<(std::ostream& os, Time const& rhs);


#endif