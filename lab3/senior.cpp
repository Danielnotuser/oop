#include <iostream>
#include <string>
#include <vector>

#include "stud.h"

namespace University
{
    Senior &Senior::set_arw(std::string topic, std::string place, int grade) 
    {
        arw.topic = topic; 
        arw.place = place; 
        arw.grade = grade; 
        return *this;
    }

    Senior &Senior::set_topic(std::string topic) 
    {
        arw.topic = topic; 
        return *this;
    }

    Senior &Senior::set_place(std::string place) 
    {
        arw.place = place; 
        return *this;
    }

    Senior &Senior::set_arw_grade(int grade) 
    {
        arw.grade = grade; 
        return *this;
    }
}
