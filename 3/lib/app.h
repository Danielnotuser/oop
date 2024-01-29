#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>
#include <vector>
#include "stud.h"
#include "group.h"
#include "table.h"

namespace University 
{
    class App;

    template <bool is_const>
    class SpecIter
    {
        private:
            TableIter<Group, std::string, is_const> group_iter;
            TableIter<Group, std::string, is_const> group_end;
            TableIter<std::shared_ptr<Student>, std::string, is_const> node;
            friend App;
            explicit SpecIter(TableIter<std::shared_ptr<Student>, std::string, is_const> node): node(node) {}
        public:
            typedef ptrdiff_t difference_type;
            typedef std::shared_ptr<Student> value_type;
            typedef std::conditional_t<is_const, const std::shared_ptr<Student>, std::shared_ptr<Student>>* pointer;
            typedef std::conditional_t<is_const, const std::shared_ptr<Student>, std::shared_ptr<Student>>& reference;
            typedef std::forward_iterator_tag iterator_category;

            // constructors
            SpecIter(TableIter<Group, std::string, is_const> it, TableIter<Group, std::string, is_const> it_end);
            template<bool other_const>
            SpecIter(const SpecIter<other_const>& o) noexcept requires (is_const >= other_const) : node(o.node) {};
            // overload
            template<bool other_const>
            SpecIter& operator =(const SpecIter<other_const>& o) noexcept requires (is_const >= other_const) {node = o.node; return *this;};
            SpecIter& operator++() noexcept;
            SpecIter operator++(int) noexcept;
            reference operator*() const noexcept {return *node;};
            template<bool other_const>
            bool operator ==(const SpecIter<other_const>& o) const noexcept {return node == o.node;};
            // other
            bool end() {return group_iter == group_end;};
    };

	/*
	* @class The most important class of the hierarchy that contains table of groups and manipuilates with it
	*/
    class App {
        private:
            Table<Group, std::string> groups;
            static std::string key(Group&);
        public:
            // constructors
            /*
            * @brief Empty constructor that creates new table of groups
            */
            App() {groups = Table<Group, std::string>(key);};
            App(std::vector<Group> gr);
            // setters & getters
            int get_group_num() {return groups.get_num();};
            // other
            void add_group(Group &gr) {groups.add(gr);};
            void del_group(std::string ind) {groups.del(ind);};
            void print_group(std::ostream&, Group&);
            /*
            * @brief Enroll student to the university
            * @param std::shared_ptr<Student> Student to enroll
            * @param Group& group where student is enrolling
            */
            void enroll_stud(std::shared_ptr<Student>, Group&);
            /*
            * @brief Change semester for the group
            * @param Group&& Group that changes
            * @param std::vector<int> New numbers of grades
            * @param std::vector<std::string> Topics for the ARW's if Student become a Senior
            * @return Group& Our groups that has been changed
            */
            Group &group_change_sem(Group&&, std::vector<int>, std::vector<std::string>);
            /*
            * @brief Average grade by the group
            */
            double group_gpa(Group&);
            Group &find_group(std::string &ind) {return groups.find(ind);}
            /*
            * @brief This method generated random marks for all students from all groups
            */
            void rand_marks();
            /*
            * @brief Method print all groups indexes with all students' surnames
            */
            void print(std::ostream&);
            void print_with_iter(std::ostream&);
            /*
            * @brief Method print all groups indexes with all students' surnames and their grades
            */
            void print_with_grades(std::ostream&);
            /*
            * @brief Method finding students that have greater or equal to 3 bad grades(F)
            * @return std::vector<std::shared_ptr<Student>> Returns vector of all this students
            */
            std::vector <std::shared_ptr<Student>> find_losers();
            /*
            * @brief Version of find_losers() with multithreading
            */
            std::vector <std::shared_ptr<Student>> multithread_losers();
            // destructors
            ~App() = default;
    };
}

#endif
