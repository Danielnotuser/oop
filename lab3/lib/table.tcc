#include <iostream>
#include <string>
#include <vector>

#include "table.h"

namespace University
{
    template <class T>
    void Table<T>::link(Elem<T> *fir, Elem<T> *sec)
    {
        fir->next = sec;
        sec->prev = fir;
    }

    template <class T>
    List<T> *Table<T>::create_map()
    {
        auto *h = new List<T>[cap];
        for (int i = 0; i < cap; i++)
        {
            link(h[i].before_begin, h[i].after_end);
            if (i == cap - 1) link(h[i].after_end, h[0].before_begin);
            else link(h[i].after_end, h[i + 1].before_begin);
        }
        return h;
    }

    template <class T>
    Table<T>::Table(std::vector<T> vect, std::string (*key_func) (T))
    {
        cap = 30;
        key = key_func;
        elem_num = vect.size();
        hash_map = create_map();
        for (int i = 0; i < elem_num; i++)
            add(vect[i]);
    }

    template <class T>
    Table<T>::Table (const Table<T> &tbl) : cap(tbl.cap), elem_num(tbl.elem_num)
    {
        if (elem_num)
        {
            hash_map = new List<T>[cap];
            std::copy(tbl.hash_map, tbl.hash_map + cap, hash_map);
        }
    }

    template <class T>
    Table<T>::Table (Table<T> &&tbl) noexcept : hash_map(tbl.hash_map), cap(tbl.cap), elem_num(tbl.elem_num)
    {
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
    }

    template <class T>
    Table<T> &Table<T>::operator=(const Table<T> &tbl)
    {
        if (this != &tbl)
        {
            cap = tbl.cap;
            elem_num = tbl.elem_num;
            delete [] hash_map;
            if (cap)
                hash_map = new List<T>[cap];
            if (elem_num)
                std::copy(tbl.hash_map, tbl.hash_map + cap, hash_map);

        }
        return *this;
    }

    template <class T>
    Table<T> &Table<T>::operator=(Table<T> &&tbl) noexcept
    {
        hash_map = tbl.hash_map;
        cap = tbl.cap;
        elem_num = tbl.elem_num;
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
        return *this;
    }

    template <class T>
    int Table<T>::hash(std::string h_key) {
        int sum = 0;
        for (int i = 0; i < h_key.length(); i++)
            sum += h_key[i];
        return sum % cap;
    }

    template <class T>
    int Table<T>::cmp(const T& val1, const T& val2)
    {
        return key(val1).compare(key(val2));
    }

    template <class T>
    void Table<T>::insert(Elem<T> *ins, Elem<T> *nxt)
    {
        ins->next = nxt;
        ins->prev = nxt->prev;
        nxt->prev->next = ins;
        nxt->prev = ins;
        elem_num++;
    }

    template <class T>
    void Table<T>::add(T val)
    {
        int h = hash(key(val));
        struct Elem<T> *a;
        a->value = val;
        struct Elem<T> *el = hash_map[h].before_begin->next;
        if (!el)
        { // Element is placed at the beginning
            insert(a, hash_map[h].after_end);
            return;
        }
        while (el != hash_map[h].after_end)
        {
            if (cmp(a->value, el->value) <= 0)
            { // Element is placed at the middle
                insert(a, el);
                return;
            }
            el = el->next;
        } // Element is placed at the end
        insert(a, hash_map[h].after_end);
    }

    template <class T>
    void Table<T>::print()
    {
        for (int i = 0; i < Table<T>::cap; i++)
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

    template <class T>
    T &Table<T>::find(std::string k)
    {
    	int h = hash(k);
    	Elem<T> *el = hash_map[h].before_end->next;
    	while (el != hash_map[h].after_end)
    	{
    		if (key(el->value) == k) 
    			return el->value;
    	}
    	throw std::runtime_error("there is no such group");
    }
}

