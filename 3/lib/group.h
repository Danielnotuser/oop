#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include "stud.h"
#include "table.h"

namespace University 
{
    class Group {
        private:
            Table<std::shared_ptr<Student>, std::string>studs;
            static std::string key(std::shared_ptr<Student>&);
            std::string index;
            int grades_num;
            int sem;
        public:
            // constructors
            Group() {studs = Table<std::shared_ptr<Student>, std::string>(key);};
            Group(std::string index, int sem);
            Group(std::string index, std::vector<std::shared_ptr<Student>>students, int sem);
            Group(std::string index, Table <std::shared_ptr<Student>, std::string> studs, int sem);
            Group(const Group& gr) = default;
            Group(Group&& gr) : studs(std::move(gr.studs)), index(std::move(gr.index)), grades_num(gr.grades_num), sem(gr.sem)
                {gr.studs = Table<std::shared_ptr<Student>, std::string>();};
            // overload
            Group &operator=(const Group&) = default;
            Group &operator=(Group&&) noexcept;
            explicit operator bool();
            // setters & getters
            std::string get_index() const {return index;};
            int get_sem() const {return sem;};
            int get_grnum() const {return grades_num;};
            int get_num() const {return studs.get_num();};
            Table<std::shared_ptr<Student>, std::string> get_studs() {return std::move(studs);};
            Group &set_sem(int s) {sem = s; return *this;};
            Group &set_grnum(int num) {grades_num = num; return *this;};
            Group &set_studs(Table <std::shared_ptr<Student>, std::string> students) {studs = std::move(students); return *this;};
            // other
            void add_stud(std::shared_ptr<Student> &st) {if (int n = st->get_grades_num() > grades_num) grades_num = n; studs.add(st);};
            std::shared_ptr<Student> find_stud(std::string &name) {return studs.find(name);};
            void print(std::ostream &c) {studs.print(c);};
            ~Group() = default;
    };
}

#endif
