#include <iostream>
#include <string>
#include <vector>

#include "table.h"

namespace University
{
    template <class T, class K>
    void Table<T,K>::link(Elem<T> *fir, Elem<T> *sec)
    {
        fir->next = sec;
        sec->prev = fir;
    }

    template <class T, class K>
    List<T> *Table<T,K>::create_map()
    {
        List<T> *h = new List<T>[cap];
        for (int i = 0; i < cap; i++)
        {
            link(h[i].before_begin, h[i].after_end);
            if (i == cap - 1) link(h[i].after_end, h[0].before_begin);
            else link(h[i].after_end, h[i + 1].before_begin);
        }
        return h;
    }

    template <class T, class K>
    Table<T,K>::Table(std::vector<T> vect, K (*key_func) (T&), int new_cap)
    {
        try
        {
            if (new_cap <= 0)
                throw std::invalid_argument("invalid capacity");
            cap = new_cap;
            key = key_func;
            elem_num = vect.size();
            hash_map = create_map();
            for (int i = 0; i < elem_num; i++)
                add(std::move(vect[i]));
        }
        catch (...)
        {
            delete [] hash_map;
            throw;
        }
    }

    template <class T, class K>
    Table<T,K>::Table(const Table<T,K> &tbl) : cap(tbl.cap), elem_num(tbl.elem_num)
    {
        if (hash_map)
            delete [] hash_map;
        if (tbl.hash_map)
        {
            key = tbl.key;
            hash_map = create_map();
            hash_map = tbl.hash_map;
        }
    }

    template <class T, class K>
    Table<T,K>::Table(Table<T,K> &&tbl) noexcept : hash_map(tbl.hash_map), cap(tbl.cap), elem_num(tbl.elem_num)
    {
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
    }

    template <class T, class K>
    Table<T,K> &Table<T,K>::operator=(const Table<T,K> &tbl)
    {
        if (this != &tbl)
        {
            cap = tbl.cap;
            elem_num = tbl.elem_num;
            key = tbl.key;
            delete [] hash_map;
            if (cap && elem_num)
            {
                for (TableIter<T,K,true> it = tbl.begin(); it != tbl.end(); it++)
                    if (*it) add(*it);
            }
        }
        return *this;
    }

    template <class T, class K>
    Table<T,K> &Table<T,K>::operator=(Table<T,K> &&tbl) noexcept
    {
        hash_map = tbl.hash_map;
        cap = tbl.cap;
        elem_num = tbl.elem_num;
        key = tbl.key;
        tbl.hash_map = nullptr;
        tbl.elem_num = 0;
        return *this;
    }

    template <class T, class K>
    int Table<T,K>::hash(K h_key) {
        int sum = 0;
        for (int i = 0; i < h_key.length(); i++)
            sum += h_key[i];
        return sum % cap;
    }

    template <class T, class K>
    int Table<T,K>::cmp(T& val1, T& val2) const
    {
        return key(val1).compare(key(val2));
    }

    template <class T, class K>
    void Table<T,K>::insert(Elem<T> *ins, Elem<T> *nxt)
    {
        ins->next = nxt;
        ins->prev = nxt->prev;
        nxt->prev->next = ins;
        nxt->prev = ins;
        elem_num++;
    }

    template <class T, class K>
    void Table<T,K>::add(T val)
    {
        int h = hash(key(val));
        Elem<T> *a = new Elem<T>;
        a->val = val;
        if (hash_map[h].before_begin->next == hash_map[h].after_end)
        { // Element is placed at the beginning
            insert(a, hash_map[h].after_end);
            return;
        }
        struct Elem<T> *el = hash_map[h].before_begin->next;
        while (el != hash_map[h].after_end)
        {
            if (cmp(a->val, el->val) <= 0)
            { // Element is placed at the middle
                insert(a, el);
                return;
            }
            el = el->next;
        } // Element is placed at the end
        insert(a, hash_map[h].after_end);
    }

    template <class T, class K>
    void Table<T,K>::del(K name)
    {
        int h = hash(name);
        Elem<T> *el = hash_map[h].before_begin->next;
        while (el != hash_map[h].after_end)
        {
            if (key(el->val) == name)
            {
                link(el->prev, el->next);
                return;
            }
            el = el->next;
        }
        throw std::invalid_argument("there is no element with this key");
    }

    template <class T, class K>
    void Table<T,K>::print(std::ostream &c)
    {
        for (int i = 0; i < cap; i++)
        {
            Elem<T> *a = hash_map[i].before_begin->next;
            while (a != hash_map[i].after_end)
                c << key(a->val) << std::endl;
        }
    }

    template <class T, class K>
    T &Table<T,K>::find(K name)
    {
    	int h = hash(name);
    	Elem<T> *el = hash_map[h].before_begin->next;
    	while (el != hash_map[h].after_end)
    	{
    		if (key(el->val) == name)
    			return el->val;
            el = el->next;
    	}
    	throw std::invalid_argument("there is no element with this key");
    }
}

