#include <iostream>
#include <string>
#include <vector>

#include "../lib/table.h"

namespace University 
{
    template <class T, class K>
    Table<T,K>::Table(std::vector<T> vect, K (*key_func) (T), int cap = 30)
    {
        key = key_func;
        elem_num = vect.size();
        for (int i = 0; i < elem_num; i++)
            add(vect[i]);
    }

    template <class T, class K>
    Table<T,K>::Table (Table<T,K> &&tbl) : hash_map(tbl.hash_map), cap(tbl.cap), elem_num(tbl.elem_num)
    {
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
    } 

    template <class T>
    int Table<T, std::string>::hash(std::string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i];
        return sum % cap;
    }

    template <class T>
    int Table<T, int>::hash(int key)
    {
        return key % cap;
    }

    template <class T>
    int cmp(const T &val1, const T &val2)
    {
        return name(val1).compare(name(val2));
    }

    template <class T, class K>
    void Table<T,K>::add(T val)
    {
        int h = hash(key(val));
        struct Elem<T> *a;
        a->value = val;
        a->next = nullptr;
        struct Elem<T> *el = hash_map[h].head;
        struct Elem<T> *pref;
        if (!el)
            hash_map[h].head = a;
        while (el)
        {
            if (cmp(a->value, el->value) <= 0)
            {
                a->next = el;
                if (el == hash_map[h].head)
                    hash_map[h].head = a;
                else
                    pref->next = a;
                elem_num++;
                return;
            }
            pref = el;
            el = el->next;
        }
        pref->next = &a;
        elem_num++;
    }

    template <class T, class K>
    Table<T,K> &Table<T,K>::operator=(Table<T,K> &&tbl) noexcept
    {
        hash_map = tbl.hash_map;
        cap = tbl.cap;
        elem_num = tbl.elem_num;
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
        return *this;
    }

    template <class T, class K>
    void Table<T,K>::print()
    {
        for (int i = 0; i < cap; i++)
        {
            Elem<T> *hd = hash_map[i].head;
            while (hd)
            {
                std::cout << key(hd->val) << " ";
                hd = hd->next;
            }
            std::cout << std::endl;
        }
    }
}

