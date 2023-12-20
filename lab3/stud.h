#ifndef STUD_H
#define STUD_H

#include <iostream>
#include <string>
#include <vector>
#include "templ.h"

namespace University 
{
    class App {
        private:
            Table<Group*> groups;
        public:
            App(std::vector<Group*> gr) : groups(gr) {};
    };

    class Student {
        private:
            std::string surname, inits;
            std::vector <int> grades;
            int grades_num = 0;
            void check_name();
        public:
            // constructors
            Student(std::string surname, std::string initials) : surname(surname), inits(initials) {check_name();};
            Student(std::string surname, std::string initials, std::vector <int> grades, int num) : 
                    surname(surname), inits(initials), grades_num(num), grades(grades) {check_name();};
            // setters & getters
            std::string get_surname() const {return surname;};
            std::string get_initials() const {return inits;};
            std::vector <int> get_grades() const {return grades;};
            Student &set_surname(std::string sur);
            Student &set_initials(std::string ins);
            Student &set_grades(std::vector <int> grades_vect, int num);                                                    
            // other
            virtual void change_sem();
    };

    // ARW - Academic and research work
    typedef struct AcademicWork {
        std::string topic, place;
        int grade;
        AcademicWork() {};
        AcademicWork(std::string t, std::string p, int g) : topic(t), place(p), grade(g) {};
    } AcademicWork;

    class Senior : public Student {
        private:
            AcademicWork arw;
        public:
            // constructors
            Senior(std::string surname, std::string ins) : Student(surname, ins) {};
            Senior(std::string surname, std::string ins, std::string topic) : Student(surname, ins) {arw.topic = topic;};
            Senior(std::string surname, std::string ins, std::string topic, std::string place, int grade) : 
                    Student(surname, ins), arw(topic, place, grade) {};
            // setters & getters
            std::string get_topic() const {return arw.topic;};
            std::string get_place() const {return arw.place;};
            int get_arw_grade() const {return arw.grade;};
            Senior &set_arw(std::string topic, std::string place, int grade) {arw.topic = topic; arw.place = place; arw.grade = grade; return *this;};
            Senior &set_topic(std::string topic) {arw.topic = topic; return *this;};
            Senior &set_place(std::string place) {arw.place = place; return *this;};
            Senior &set_arw_grade(int grade) {arw.grade = grade; return *this;};
            // other
            void change_sem() override;
    };

    class Group {
        private:
            Table <Student*> studs;
            std::string index;
            int grades_num;
            int sem;
            int stud_type;
        public:
            // constructors
            Group(std::string index, std::vector<Student*>students, int grades_num, int sem, int stud_type) :
                studs(students), index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) {};
            Group(std::string index, Table <Student*> studs, int grades_num, int sem, int stud_type) :
                studs(std::move(studs)), index(index), grades_num(grades_num), sem(sem), stud_type(stud_type) {};
            // setters & getters
            std::string get_index() const {return index;};
            int get_grnum() const {return grades_num;};
            Group &set_type(int stud) {stud_type = stud; return *this;};
            Group &set_sem(int s) {sem = s; return *this;};
            Group &set_grnum(int num) {grades_num = num; return *this;};
            Group &set_studs(Table <Student*> students) {studs = std::move(students); return *this;};
    };
}


#endif