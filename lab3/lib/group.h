#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <string>
#include <vector>
#include "stud.h"
#include "table.h"

namespace University 
{
    class Group {
        private:
            Table <Student*> studs;
            std::string index;
            int grades_num;
            int sem;
            int stud_type;
        public:
            // constructors
            Group(std::string index, std::vector<Student*>students, int grades_num, int sem, int stud_type) :
                studs(students), index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) {};
            Group(std::string index, Table <Student*> studs, int grades_num, int sem, int stud_type) :
                studs(std::move(studs)), index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) {};
            // setters & getters
            std::string get_index() const {return index;};
            int get_grnum() const {return grades_num;};
            Group &set_type(int stud) {stud_type = stud; return *this;};
            Group &set_sem(int s) {sem = s; return *this;};
            Group &set_grnum(int num) {grades_num = num; return *this;};
            Group &set_studs(Table <Student*> students) {studs = std::move(students); return *this;};
    };
}

#endif
