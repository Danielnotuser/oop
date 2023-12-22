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
            Table<Group*> groups;
        public:
            App(std::vector<Group*> gr) : groups(gr) {};
    };
}

#endif