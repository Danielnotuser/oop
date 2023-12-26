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
        public:
            // constructors
            App(std::vector<Group> gr);
            // setters & getters
            int get_group_num() {return groups.get_num();};
            // other
            void add_group(Group gr) {groups.add(gr);};
    };
}

#endif
