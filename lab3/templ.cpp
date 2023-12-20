#include <iostream>
#include <string>
#include <vector>

#include "stud.h"
#include "templ.h"

namespace University 
{
    template <class T>
    int Table<T>::hash(std::string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i];
        return sum % cap;
    }
    /*
    template <class T>
    int Table<T>::hash(std::string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i] / (i + 1);
        return sum % cap;
    }
    */

    template <class T>
    int cmp(const T &val1, const T &val2)
    {
        return std::string::compare(name(val1), name(val2));
    }

    template <class T>
    Table<T>::Table(std::vector<T>vect)
    {
        std::sort(vect, vect + vect.size(), cmp<T>);
        elem_num = vect.size();
        for (int i = 0; i < elem_num; i++)
            add(vect[i]);
    }
    
    std::string Table<Student*>::name(Student* val)
    {
        return val->get_surname();
    }

    std::string Table<Group*>::name(Group* val)
    {
        return val->get_index();
    }

    template <class T>
    void Table<T>::add(T val)
    {
        int h = hash(name(T));
        struct Elem<T> a;
        a.value = val;
        a.next = nullptr;
        struct Elem<T> *el = hash_map[h].head;
        struct Elem<T> *pref;
        if (!el)
            hash_map[h].head = &a;
        while (el)
        {
            pref = el;
            el = el->next;
        }
        pref->next = &a;
        elem_num++;
    }

    template <class T>
    void Table<T>::print()
    {
        for (int i = 0; i < cap; i++)
        {
            Elem *hd = hash_map[i].head;
            while (hd)
            {
                std::cout << name(hd->val) << std::endl;
                hd = hd->next;
            }
        }
    }
}

