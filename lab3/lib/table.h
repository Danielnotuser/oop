#ifndef TEMPL_H
#define TEMPL_H

#include <vector>

namespace University
{
    // structs for List of T values
    template <class T>
    struct Elem {
        T value;
        struct Elem<T> *prev;
        struct Elem<T> *next;
    };
    template <class T>
    struct List {
        struct Elem<T> *before_begin;
        struct Elem<T> *after_end;
    };
    // template for Students and Groups
    template <class T>
    class Table {
        private:
            List<T> *hash_map;
            int cap;
            int elem_num = 0;
            void link(Elem<T>*,Elem<T>*);
            List<T>* create_map();
            int hash(std::string);
            static std::string key(T);
            int cmp(const T&, const T&);
            void insert(Elem<T>*,Elem<T>*);
        public:
            // constructors
            explicit Table<T>(int cap = 30) : cap(cap) {hash_map = create_map();};
            Table<T>(std::vector<T>, std::string (*) (T), int = 30);
            Table<T>(const Table&);
            Table<T>(Table&&) noexcept;
            // setters & getters
            int get_cap() const {return cap;};
            int get_num() const {return elem_num;};
            List<T> *get_map() const {return hash_map;};
            Table<T> &set_elem_num(int num) {elem_num = num; return *this;};
            // overload
            Table<T> &operator=(const Table<T>&);
            Table<T> &operator=(Table<T>&&) noexcept;
            // other
            void add(T);
            void print();
            // destructor
            ~Table<T>() {delete [] hash_map;};

    };
}

#include "table.tcc"

#endif
