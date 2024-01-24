#include "../lib/stud.h"

namespace University
{
    Senior &Senior::set_arw(std::string topic, std::string place, int grade) 
    {
        arw.topic = std::move(topic);
        arw.place = std::move(place);
        arw.grade = grade; 
        return *this;
    }

    Senior &Senior::set_topic(std::string topic) 
    {
        arw.topic = std::move(topic);
        return *this;
    }

    Senior &Senior::set_place(std::string place) 
    {
        arw.place = std::move(place);
        return *this;
    }

    Senior &Senior::set_arw_grade(int grade) 
    {
        arw.grade = grade; 
        return *this;
    }
}
