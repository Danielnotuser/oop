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
            Table<Group, std::string> groups;
            static std::string key(Group&);
        public:
            // constructors
            App() {groups = Table<Group, std::string>(key);};
            App(std::vector<Group> gr);
            // setters & getters
            int get_group_num() {return groups.get_num();};
            // other
            void add_group(Group &gr) {groups.add(std::move(gr));};
            void print_group(std::ostream&, Group&);
            void enroll_stud(std::shared_ptr<Student>, Group&);
            void change_sem(Group&, std::shared_ptr<Student>, int);
            double gpa(Group&);
            Group &find_group(std::string ind) {return groups.find(ind);}
            void print(std::ostream&);
            void print_with_grades(std::ostream&);
            std::vector <std::shared_ptr<Student>> find_losers();
            
            // destructors
            ~App() = default;
    };
}

#endif
