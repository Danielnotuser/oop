#ifndef TEMPL_H
#define TEMPL_H

#include <vector>
#include <iterator>
#include <memory>

namespace University
{
    template<class T, class K>
    class Table;
    // struct for Element of List
    template <class T>
    struct Elem {
        T val = T{};
        struct Elem<T> *prev = nullptr;
        struct Elem<T> *next = nullptr;
    };
    // List of T values
    template <class T>
    struct List {
        struct Elem<T> *before_begin = nullptr;
        struct Elem<T> *after_end = nullptr;
        List() {before_begin = new Elem<T>; after_end = new Elem<T>;};
        ~List() {
            if (before_begin != nullptr)
            {
                Elem<T> *a = before_begin;
                Elem<T> *b;
                while (a != after_end)
                {
                    b = a;
                    a = a->next;
                    delete b;
                }
                delete a;
            }
        };
    };

    /**
	* @class TableIter Iterator of template Table class
	*/
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


    /**
    * @class Table Class that contains array of lists with hash 
    * @brief T stands for type of value and K stands for type of key
    */
    template <class T, class K>
    class Table {
        private:
            List<T> *hash_map = nullptr;
            int cap;
            int elem_num = 0;
            K (*key) (T&);
            List<T>* create_map();
            int hash(K);
            int cmp(T&, T&) const;
            void link(Elem<T>*,Elem<T>*);
            void insert(Elem<T>*,Elem<T>*);
        public:
            // constructors
            /**
            * @brief Construct an empty object
            */
            Table() {};
            /**
            * @brief Constructor that creates empty hash_map with key func
            * @param key_func Function for returning a key of T value
            * @param cap Capacity of hash_map
            * @throw std::invalid_argument if cap unpositive
            * @throw error to catch and free the hash_map
            */
            Table(K (*key_func) (T&), int cap = 30) : cap(cap) {key = key_func; hash_map = create_map();};
            /**
            * @brief Constructor that fill hash_map with values from vector
            * @param vect Vector of T values that will be added
            * @param key_func Function for returning a key of T value
            */
            Table(std::vector<T> vect, K (*key_func) (T&), int = 30);
            /**
            * @brief Copying contructor
            */
            Table(const Table<T,K>&);
            /**
            * @brief Moving contructor
            */
            Table(Table<T,K>&&) noexcept;
            // setters & getters
            int get_cap() const {return cap;};
            /**
            * @brief Getter for number of elements
            * @return int Number of actual values
            */
            int get_num() const {return elem_num;};
            Table &set_elem_num(int num) {elem_num = num; return *this;};
            // overload
            /**
            * @brief Copying assignment
            */
            Table &operator=(const Table<T,K>&);
            /**
            * @brief Moving assignment
            */
            Table &operator=(Table<T,K>&&) noexcept;
            // other
            /**
            * @brief Method for adding a value to the hash_map
            * @param v T value
            */
            void add(T v);
            /**
            * @brief Delete value by its key
            * @param k Key of value
            * @throw std::invalid_argument if there is no value with this key
            */
            void del(const K& k);
            /**
            * @brief Table print
            * @param c Stream for output
            */
            void print(std::ostream& с);
            /**
            * @brief Find value by key
            * @param k key of value
            * @throw std::invalid_argument if there is no value with this key
            */
            T &find(const K& k);
            bool is_empty() {return (elem_num == 0);};
            // iterator
            /**
            * @brief Iterator to the beginning of the map
            * @return TableIter const iterator of iterator
            */
            TableIter<T, K, true> begin() const {return TableIter<T, K, true>(hash_map[0].before_begin->next);};
            TableIter<T, K, false> begin() {return TableIter<T, K, false>(hash_map[0].before_begin->next);};
            TableIter<T, K, true> end() const {return TableIter<T, K, true>(hash_map[cap-1].after_end);};
            TableIter<T, K, false> end() {return TableIter<T, K, false>(hash_map[cap-1].after_end);};
            // destructor
            ~Table() {delete [] hash_map;};
    };

}

#include "table.tcc"

#endif
