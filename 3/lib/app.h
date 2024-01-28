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
            void add_group(Group &gr) {groups.add(gr);};
            void del_group(std::string ind) {groups.del(ind);};
            void print_group(std::ostream&, Group&);
            void enroll_stud(std::shared_ptr<Student>, Group&);
            Group &group_change_sem(Group&&, std::vector<int>, std::vector<std::string>);
            double group_gpa(Group&);
            Group &find_group(std::string &ind) {return groups.find(ind);}
            void rand_marks();
            void print(std::ostream&);
            void print_with_grades(std::ostream&);
            std::vector <std::shared_ptr<Student>> find_losers();
            std::vector <std::shared_ptr<Student>> multithread_losers();
            // destructors
            ~App() = default;
    };
}

#endif
