#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>
#include <vector>
#include "stud.h"
#include "group.h"
#include "table.h"

namespace University 
{
    class App {
        private:
            Table<Group> groups;
        public:
            // constructors
            App(std::vector<Group> gr);
            // setters & getters
            int get_group_num() {return groups.get_num();};
            // other
            void add_group(Group gr) {groups.add(gr);};
            void enroll_stud(Student&, std::string);
            void change_sem(Student*, int);
            double gpa(Group);
            
            // destructors
            ~App() = default;
    };
}

#endif
