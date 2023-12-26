#ifndef STUD_H
#define STUD_H

#include <iostream>
#include <string>
#include <vector>
#include "table.h"

namespace University 
{
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
            Student(Student&& st) : surname(st.get_surname()), inits(st.get_initials()), 
                                    grades_num(st.get_grades_num()), grades(st.get_grades()) {};
            // setters & getters
            std::string get_surname() const {return surname;};
            std::string get_initials() const {return inits;};
            int get_grades_num() const {return grades_num;};
            std::vector <int> get_grades() const {return grades;};
            Student &set_surname(std::string sur);
            Student &set_initials(std::string ins);
            Student &set_grades(std::vector <int> grades_vect, int num);                                                    
            // other
            virtual void change_sem();
            // destructor
            virtual ~Student() = default;
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
            Senior(Student &stud) : Student(std::move(stud)) {};
            Senior(Student &stud, std::string topic) : Student(std::move(stud)) {arw.topic = topic;};
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
            // destructor
            ~Senior() override = default;
    };
}

#endif