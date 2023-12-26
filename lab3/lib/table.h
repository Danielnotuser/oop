#ifndef TEMPL_H
#define TEMPL_H

#include <vector>
#include "../src/table.tcc"

namespace University
{
    // structs for List of T values
    template <class T>
    struct Elem {
        T value;
        struct Elem<T> *next;
    };
    template <class T>
    struct List {
        struct Elem<T> *head;
    };
    // template for Students and Groups
    template <class T, class K>
    class Table {
        private:
            List<T> *hash_map;
            int cap;
            int elem_num;
            int hash(K);
            K key(T);
            int cmp(T);
        public:
            // constructors
            Table(std::vector<T>, K (*) (T), int);
            Table(Table&&);
            // setters & getters
            int get_cap() const {return cap;};
            int get_num() const {return elem_num;};
            List<T> *get_map() const {return hash_map;};
            Table<T,K> &set_elem_num(int num) {elem_num = num; return *this;};
            // overload
            Table<T,K> &operator=(Table<T,K>&&) noexcept;
            // other
            void add(T);
            void print();
            // destructor
            ~Table() {delete [] hash_map;};

    };
}



#endif
