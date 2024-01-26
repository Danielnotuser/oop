#ifndef TEMPL_H
#define TEMPL_H

#include <vector>
#include <iterator>

namespace University
{
    template<class T, class K>
    class Table;
    // structs for List of T values
    template <class T>
    struct Elem {
        T val = T{};
        struct Elem<T> *prev = nullptr;
        struct Elem<T> *next = nullptr;
    };
    template <class T>
    struct List {
        struct Elem<T> *before_begin = nullptr;
        struct Elem<T> *after_end = nullptr;
    };

    template<class T, class K, bool is_const>
    class TableIter
    {
    private:
        typedef std::conditional_t<is_const, const Elem<T>, Elem<T>>*node_ptr_t;
        node_ptr_t node;
        explicit TableIter(node_ptr_t node): node(node) {}
        friend Table<T,K>;
        friend TableIter<T, K, !is_const>;
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef std::conditional_t<is_const, const T, T>* pointer;
        typedef std::conditional_t<is_const, const T, T>& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        // constructors
        TableIter() noexcept : node(nullptr) {};
        template<bool other_const>
        TableIter(const TableIter<T, K, other_const>& o) noexcept requires (is_const >= other_const) : node(o.node) {};
        // overload
        template<bool other_const>
        TableIter& operator =(const TableIter<T, K, other_const>& o) noexcept requires (is_const >= other_const) {node = o.node; return *this;};
        TableIter& operator++() noexcept {node = node->next; return *this;};
        TableIter operator++(int) noexcept {TableIter res(node); node = node->next; return res;};
        TableIter& operator--() noexcept {node = node->prev; return *this;};
        TableIter operator--(int) noexcept {TableIter res(node); node = node->prev; return res;};
        reference operator*() const noexcept {return node->val;};
        pointer operator->() const noexcept {return &node->val;};
        template<bool other_const>
        bool operator ==(const TableIter<T, K, other_const>& o) const noexcept {return node == o.node;};

    };
    // template for Students and Groups
    template <class T, class K>
    class Table {
        private:
            List<T> *hash_map;
            int cap;
            int elem_num = 0;
            void link(Elem<T>*,Elem<T>*);
            List<T>* create_map();
            static K (*key) (T&);
            int hash(K);
            int cmp(T&, T&) const;
            void insert(Elem<T>*,Elem<T>*);
        public:
            // constructors
            Table() {};
            Table(K (*key_func) (T&), int cap = 30) : cap(cap) {key = key_func; hash_map = create_map();};
            Table(std::vector<T>, K (*) (T&), int = 30);
            Table(const Table<T,K>&);
            Table(Table<T,K>&&) noexcept;
            // setters & getters
            int get_cap() const {return cap;};
            int get_num() const {return elem_num;};
            Table &set_elem_num(int num) {elem_num = num; return *this;};
            // overload
            Table &operator=(const Table<T,K>&);
            Table &operator=(Table<T,K>&&) noexcept;
            // other
            void add(T);
            void del(K);
            void print(std::ostream&);
            T &find(K);
            bool is_empty() {return (elem_num == 0);};
            // iterator
            template<bool is_const>
            TableIter<T, K, is_const> begin() {return TableIter<T, K, is_const>(hash_map[0].before_begin->next);};
            template<bool is_const>
            TableIter<T, K, is_const> end() {return TableIter<T, K, is_const>(hash_map[cap-1].after_end);};
            // destructor
            ~Table() {delete [] hash_map;};
    };

    static_assert(std::bidirectional_iterator<TableIter<int, int, false>>);
    static_assert(std::bidirectional_iterator<TableIter<int, int, true>>);
}

#include "table.tcc"

#endif
