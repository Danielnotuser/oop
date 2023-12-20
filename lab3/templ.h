#ifndef TEMPL_H
#define TEMPL_H

#include <iostream>
#include <string>
#include <vector>

namespace University
{
    // template for Students and Groups
    template <class T>
    struct Elem {
        T value;
        struct Elem *next;
    };
    template <class T>
    struct List {
        struct Elem *head;
    };

    template <class T>
    class Table {
        private:
            std::vector<List<T>>hash_map;
            int cap;
            int elem_num;
            int hash(std::string key);
            std::string name(T);
            int cmp(T);
        public:
            // constructors
            Table(std::vector<T>vect);
            // setters & getters
            int get_cap() const {return cap;};
            int get_num() const {return elem_num;};
            // other
            void add(T);
            void print();
    };
}



#endif TEMPL_H