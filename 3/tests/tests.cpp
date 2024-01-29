#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include "../lib/app.h"

std::random_device r;

TEST_CASE("Test add method") {
    Table<int, int> table;
    table.add(r());
    REQUIRE(table.get_num() == 1);
}

TEST_CASE("Test del method") {
    Table<int, int> table;
    int a = r();
    table.add(a);
    table.del(a);
    REQUIRE(table.get_num() == 0);
}

TEST_CASE("Test find method") {
    Table<int, int> table;
    int a = r();
    table.add(a);
    REQUIRE(table.find(a) == a);
}

TEST_CASE("Test is_empty method") {
    Table<int, int> table;
    REQUIRE(table.is_empty());
    int a = r();
    table.add(a);
    REQUIRE_FALSE(table.is_empty());
}

TEST_CASE("Test get_num method") {
    Table<int, int> table;
    REQUIRE(table.get_num() == 0);
    int a = r();
    table.add(a);
    REQUIRE(table.get_num() == 1);
}

TEST_CASE("Test default constructor") {
    Table<int, int> table;
    REQUIRE(table.get_num() == 0);
}

TEST_CASE("Test copy constructor") {
    Table<int, int> table1;
    int a = r();
    table.add(a);
    Table<int, int> table2(table1);
    REQUIRE(table2.get_num() == 1);
    REQUIRE(table2.find(a) == a);
}

TEST_CASE("Test move constructor") {
    Table<int, int> table1;
    int a = r();
    table.add(a);
    Table<int, int> table2(std::move(table1));
    REQUIRE(table2.get_num() == 1);
    REQUIRE(table2.find(a) == a);
}

TEST_CASE("Test copy assignment operator") {
    Table<int, int> table1;
    int a = r();
    table.add(a);
    Table<int, int> table2;
    table2 = table1;
    REQUIRE(table2.get_num() == 1);
    REQUIRE(table2.find(a) == a);
}

TEST_CASE("Test move assignment operator") {
    Table<int, int> table1;
    int a = r();
    table.add(a);
    Table<int, int> table2;
    table2 = std::move(table1);
    REQUIRE(table2.get_num() == 1);
    REQUIRE(table2.find(a) == a);
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
