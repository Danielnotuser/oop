#ifndef TEMPL_H
#define TEMPL_H

#include <vector>
#include <iterator>

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
            int cmp(const T&, const T&) const;
            void insert(Elem<T>*,Elem<T>*);
        public:
            // constructors
            explicit Table<T>(int cap = 30) : cap(cap) {hash_map = create_map();};
            Table(std::vector<T>, std::string (*) (T), int = 30);
            Table<T>(const Table&);
            Table<T>(Table&&) noexcept;
            // setters & getters
            int get_cap() const {return cap;};
            int get_num() const {return elem_num;};
            Table<T> &set_elem_num(int num) {elem_num = num; return *this;};
            // overload
            Table<T> &operator=(const Table<T>&);
            Table<T> &operator=(Table<T>&&) noexcept;
            // other
            void add(T);
            void print();
            T &find(std::string);
            // iterator
            class TableIter
            {
				private:
					Elem<T> *node;
				public:
					typedef ptrdiff_t difference_type;
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef std::bidirectional_iterator_tag iterator_category;
				
					friend Table<T>;
					// constructors
					TableIter() noexcept : node(nullptr) {};
					TableIter(Elem<T> *node) : node(node) {};
					TableIter(TableIter& obj) : node(obj.node) {};
					// overload
					TableIter& operator=(const TableIter& obj) {node = obj.node; return *this;};
					//TableIter& operator=(TableIter&&obj) noexcept {node = obj.node; obj.node = nullptr; return *this;};
					TableIter &operator++() noexcept {node = node->next; return *this;};
					TableIter operator++(int) noexcept {TableIter res(node); node = node->next; return res;};
					TableIter &operator--() noexcept {node = node->prev; return *this;};
					TableIter operator--(int) noexcept {TableIter res(node); node = node->prev; return res;};
					T &operator*() const noexcept {return node->value;};
					T *operator->() const noexcept {return &node->value;};
					bool operator==(const TableIter& obj) const noexcept {return node == obj.node;};
            };
            TableIter begin() {return TableIter(hash_map[0].before_begin);};
            TableIter end() {return TableIter(hash_map[cap-1].after_end);};
            // destructor
            ~Table<T>() {delete [] hash_map;};

    };
}

#include "table.tcc"

#endif
