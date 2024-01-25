#include "Time.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

//Konstruktor

Time::Time()
{}

Time::Time(int const h , int const m , int const s)
    : hour{h}, minute{m}, second{s}
{
    if (hour >= 24 or hour < 0)
    {
        throw std::out_of_range{"Timmar måster vara [0, 23]"};
    }
    else if (minute >= 60 or minute < 0)
    {
        throw std::out_of_range{"Minuter måste vara [0,59]"};
    }
    else if (second >= 60 or second < 0)
    {
        throw std::out_of_range("Sekunder måste vara [0.59]");
    }
}

Time::Time(std::string const& t_s)
    : time_string{t_s}
{
   // string ampm{};

    hour = stoi(t_s.substr(0,2));
    minute = stoi(t_s.substr(3,2));
    second = stoi(t_s.substr(6,2));

    if (t_s.size() > 8 )
    {
        if (t_s.substr(8,2) == "pm" && hour != 12) 
        {
            hour += 12;
        }
        else if (t_s.substr(8,2) == "am" && hour == 12)
        {
            hour = 0;
        } 
    }

    if (hour >= 24 or hour < 0)
    {
        throw std::out_of_range{"Timmar måster vara [0, 23]"};
    }
    else if (minute >= 60 or minute < 0)
    {
        throw std::out_of_range{"Minuter måste vara [0,59]"};
    }
    else if (second >= 60 or second < 0)
    {
        throw std::out_of_range("Sekunder måste vara [0.59]");
    }
}


//Functions

string Time::to_string(bool us) const
{
    std::ostringstream oss {};
    int tmp_hour {hour};
    if (us)
    {
        if (hour >= 12)
        {          
            if (hour > 12)
            {
                tmp_hour -= 12;
            } 
            
            oss << std::setw(2) << std::setfill('0') << tmp_hour << ':' << std::setw(2) << std::setfill('0') << minute << ':' << std::setw(2) << std::setfill('0') << second << "pm";
        }
        else
        {
            if (hour == 0)
            {
                tmp_hour += 12;
            }
            
            oss << std::setw(2) << std::setfill('0') << tmp_hour << ':' << std::setw(2) << std::setfill('0') << minute << ':' << std::setw(2) << std::setfill('0') << second << "am";
        }    
    }
    else
    {
        oss << std::setw(2) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ':' << std::setw(2) << std::setfill('0') << second;
    }
    
    return oss.str();
}

bool Time::is_am() const
{
    return hour < 12;
}

int Time::get_hour() const
{
    return hour;
}
int Time::get_minute() const
{
    return minute;
}
int Time::get_second() const
{
    return second;
}

//Operatorer

Time& Time::operator++()
{
    second++;
    if (second == 60)
    {
        second = 0;
        minute++;
        if (minute == 60)
        {
            minute = 0;
            hour++;
            if (hour == 24)
            {
                hour = 0;
            }
        }        
    }

    return *this;
}

Time Time::operator++(int)
{
    Time tmp {*this};
    ++(*this);
    return tmp;
}

Time& Time::operator--()
{
    if (second == 0 && minute == 0 && hour == 0)
    {
        second = 59;
        minute = 59;
        hour = 23;
    }
    else if (second == 0 && minute == 0)
    {
        second = 59;
        minute = 59;
        hour--;
    }
    else if (second == 0)
    {
        second = 59;
        minute--;
    }
    else
    {
        second--;
    }
    
    
    return *this;
}

Time Time::operator--(int)
{
    Time tmp {*this};
    --(*this);
    return tmp;
}

bool Time::operator<(Time const& rhs) const
{   
    if (hour == rhs.hour && minute == rhs.minute)
    {
        return second < rhs.second;
    }
    else if (hour == rhs.hour && minute != rhs.minute)
    {
        return minute < rhs.minute;
    }
    else
    {
        return hour < rhs.hour;
    }
}

bool Time::operator>(Time const& rhs) const
{
    return rhs < *this;
}

bool Time::operator==(Time const& rhs) const
{
    return !(rhs < *this) && !(rhs > *this);
}

bool Time::operator<=(Time const& rhs) const
{
    return (*this < rhs || *this == rhs);
}

bool Time::operator>=(Time const& rhs) const
{
    return (*this > rhs || *this == rhs);
}

bool Time::operator!=(Time const& rhs) const
{
    if (rhs < *this || rhs > *this)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

std::ostream& operator<<(std::ostream& os, Time const& rhs)
{
    os << rhs.to_string();
    return os;
}
