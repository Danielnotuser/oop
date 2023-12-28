#include "../lib/stud.h"
#include "../lib/group.h"
#include "../lib/table.h"

namespace University
{
    std::string stud_name(std::shared_ptr<Student> st)
    {
        return st->get_surname();
    }
    
    Group::Group(std::string index, std::vector<std::shared_ptr<Student>> vect, int grades_num, int sem, int stud_type) :
        index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) 
    {
        studs = Table<std::shared_ptr<Student>>(vect, stud_name);
    }
}
