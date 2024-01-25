#include "../lib/stud.h"
#include "../lib/group.h"
#include "../lib/table.h"

namespace University
{
    std::string stud_name(std::shared_ptr<Student> &st)
    {
        return st->get_surname();
    }
    
    Group::Group(std::string index, std::vector<std::shared_ptr<Student>> vect, int sem) :
        index(index), sem(sem)
    {
        int max = grades_num;
        for (int i = 0; i < vect.size(); i++)
            if (vect[i]->get_grades_num() > max) max = vect[i]->get_grades_num();
        studs = Table<std::shared_ptr<Student>, std::string>(vect, stud_name);
    }

    Group::Group(std::string index, Table <std::shared_ptr<Student>, std::string> studs, int sem) :
        index(index), studs(std::move(studs)), sem(sem)
    {
        int max = grades_num;
        for (auto it = studs.begin(); it != studs.end(); it++)
            if ((*it)->get_grades_num() > max) max = (*it)->get_grades_num();
    }
}
