#include <iostream>
#include <string>
#include <vector>

#include "../lib/stud.h"

namespace University
{
    void Student::check_name()
    {
        // checking surname
        for (size_t i = 0; i < surname.length(); i++)
        {
            if (((i == 0) && !std::isupper(surname[i])) ||
                (i && !std::islower(surname[i])))
                throw std::invalid_argument("invalid surname");
        }
        // checking initials
        if (inits.length() > 2 ||
            !std::isupper(inits[0]) || (inits.length() != 1 &&!std::isupper(inits[1])))
            throw std::invalid_argument("invalid initals");

    }

    Student &Student::set_surname(std::string sur) 
    {
        surname = sur; 
        return *this;
    }

    Student &Student::set_initials(std::string ins) 
    {
        inits = ins; 
        return *this;
    }

    Student &Student::set_grades(std::vector <int> grades_vect)
    {
        grades = grades_vect;
        return *this;
    }

    double Student::get_avr()
    {
    	double sum;
    	for (int i = 0; i < grades_num; i++)
    		sum += grades[i];
    	return (double) sum / grades_num;
    }

}


