#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include "../lib/app.h"

std::random_device r;

TEST_CASE("Testing Table class with T = std::shared_ptr<University::Student> and K = std::string")
{
    SECTION("Testing constructors and getters") {
        Table<std::shared_ptr<University::Student>, std::string> table;
        REQUIRE(table.get_cap() == 30);
        REQUIRE(table.get_num() == 0);

        K (*key_func) (T&) = [](T& t) { return t->get_name(); };
        Table<std::shared_ptr<University::Student>, std::string> table2(key_func, 50);
        REQUIRE(table2.get_cap() == 50);
    }

    SECTION("Testing add, find, and delete") {
        Table<std::shared_ptr<University::Student>, std::string> table;
        std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J.", 3);
        std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A.B.", 3);

        table.add(student1);
        table.add(student2);

        REQUIRE(table.get_num() == 2);

        auto found_student = table.find("Smith");
        REQUIRE(found_student->get_surname() == "Smith");

        table.del("Doe");
        REQUIRE(table.get_num() == 1);
    }

    SECTION("Testing printing") {
        Table<std::shared_ptr<University::Student>, std::string> table;
        std::stringstream ss;
        table.print(ss);
        std::string output = ss.str();
        REQUIRE(output == "");
    }
}

TEST_CASE("Testing Student class") {
    University::Student student("Doe", "J.", 3);

    SECTION("Testing getters and setters") {
        REQUIRE(student.get_surname() == "Doe");
        REQUIRE(student.get_initials() == "J.");
        REQUIRE(student.get_grades_num() == 3);

        student.set_surname("Smith");
        student.set_initials("A.B.");
        student.set_grades({90, 85, 95});

        REQUIRE(student.get_surname() == "Smith");
        REQUIRE(student.get_initials() == "A.B.");
        REQUIRE(student.get_grades_num() == 3);
        REQUIRE(student.get_grades() == std::vector<int>{90, 85, 95});
    }

    SECTION("Testing average grade calculation") {
        student.set_grades({80, 90, 85});
        double avg = student.get_avr();
        REQUIRE(avg == Approx(85.0));
    }

    SECTION("Testing refreshing grades") {
        student.set_grades({80, 90, 85});
        student.refresh_grades(4);
        REQUIRE(student.get_grades_num() == 4);
        REQUIRE(student.get_grades().empty());
    }
}

TEST_CASE("Testing Senior class") {
    University::Senior senior("Doe", "J.", 3);

    SECTION("Testing getters and setters") {
        REQUIRE(senior.get_surname() == "Doe");
        REQUIRE(senior.get_initials() == "J.");
        REQUIRE(senior.get_grades_num() == 3);

        senior.set_surname("Smith");
        senior.set_initials("A.B.");
        senior.set_grades({90, 85, 95});

        REQUIRE(senior.get_surname() == "Smith");
        REQUIRE(senior.get_initials() == "A.B.");
        REQUIRE(senior.get_grades_num() == 3);
        REQUIRE(senior.get_grades() == std::vector<int>{90, 85, 95});

        senior.set_arw("Research", "Lab", 92);

        REQUIRE(senior.get_topic() == "Research");
        REQUIRE(senior.get_place() == "Lab");
        REQUIRE(senior.get_arw_grade() == 92);
    }
}

TEST_CASE("Testing Group class") {
    University::Group group("G1", 1);

    SECTION("Testing getters and setters") {
        REQUIRE(group.get_index() == "G1");
        REQUIRE(group.get_sem() == 1);
        REQUIRE(group.get_grnum() == 0);
        REQUIRE(group.get_num() == 0);

        group.set_sem(2);
        group.set_grnum(3);

        REQUIRE(group.get_sem() == 2);
        REQUIRE(group.get_grnum() == 3);
    }

    SECTION("Testing adding and finding students") {
        std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J.", 3);
        std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A.B.", 3);

        group.add_stud(student1);
        group.add_stud(student2);

        REQUIRE(group.get_num() == 2);

        std::string name = "Smith";
        auto found_student = group.find_stud(name);
        REQUIRE(found_student->get_surname() == "Smith");
    }

    SECTION("Testing printing students") {
        std::stringstream ss;
        group.print(ss);
        std::string output = ss.str();
        REQUIRE(output == "");
    }
}
