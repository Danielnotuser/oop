#include <iostream>
#include <string>
#include <memory>

#include "stud.h"
#include "group.h"
#include "table.h"

namespace University
{
    std::string stud_name(Student *st)
        return st->get_surname();
    
    Group::Group(std::string index, std::vector<Student*> vect, int grades_num, int sem, int stud_type) :
        index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) 
    {
        studs = Table<Student*, std::string>(vect, stud_name);
    }
}