#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include "../lib/app.h"

namespace University
{
	std::random_device r;

	TEST_CASE("Testing Table")
	{
		std::string (*key) (std::shared_ptr<Student>&) = [](std::shared_ptr<Student>& t) 
	    	       { return t->get_surname();};
	    SECTION("Testing constructors and getters") {
	        Table<std::shared_ptr<University::Student>, std::string> table;
	    
	        REQUIRE(table.get_num() == 0);

	        Table<std::shared_ptr<University::Student>, std::string> table2(key, 50);
	        REQUIRE(table2.get_cap() == 50);
	    }

	    SECTION("Testing add, find, and delete") {

	        Table<std::shared_ptr<University::Student>, std::string> table(key);
	        std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J", 3);
	        std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A", 3);

	        table.add(student1);
	        table.add(student2);
	        std::stringstream ss;
	        table.print(ss);
	        std::string output = ss.str();
	        if ((output != "Smith\nDoe\n"))
	        	REQUIRE(output == "Doe\nSmith\n");
	        else
	        	REQUIRE(output == "Smith\nDoe\n");
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
	    SECTION("Moving and copying constructors")
	    {
	    	Table<std::shared_ptr<Student>, std::string> tbl(key, 33);
	    	std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J", 3);
	    	std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A", 3);
	    	tbl.add(student1);
	    	tbl.add(student2);
	    	Table<std::shared_ptr<Student>, std::string> tbl2(tbl);
	    	REQUIRE(tbl2.get_cap() == 33);
	    	REQUIRE(tbl2.get_num() == 2);
	    	REQUIRE(tbl2.find("Doe") == student1);
	    	Table<std::shared_ptr<Student>, std::string> tbl3(std::move(tbl));
	    	REQUIRE(tbl3.get_cap() == 33);
	    	REQUIRE(tbl3.get_num() == 2);
	    	REQUIRE(tbl.get_num() == 0);
	    }
	    SECTION("Moving and copying assignment")
	    {
	    	Table<std::shared_ptr<Student>, std::string> tbl(key, 33);
	    	std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J", 3);
	    	std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A", 3);
	    	tbl.add(student1);
	    	tbl.add(student2);
	    	Table<std::shared_ptr<Student>, std::string> tbl2;
	    	tbl2 = tbl;
	    	REQUIRE(tbl2.get_cap() == 33);
	    	REQUIRE(tbl2.get_num() == 2);
	    	REQUIRE(tbl2.find("Doe") == student1);
	    	Table<std::shared_ptr<Student>, std::string> tbl3;
	    	tbl3 = std::move(tbl);
	    	REQUIRE(tbl3.get_cap() == 33);
	    	REQUIRE(tbl3.get_num() == 2);
	    	REQUIRE(tbl3.find("Smith") == student2);
	    	REQUIRE(tbl.get_num() == 0);
	    }
	    
	}

	TEST_CASE("Testing Student class") {
	    University::Student student("Doe", "J", 3);

	    SECTION("Testing getters and setters") {
	        REQUIRE(student.get_surname() == "Doe");
	        REQUIRE(student.get_initials() == "J");
	        REQUIRE(student.get_grades_num() == 3);

	        student.set_surname("Smith");
	        student.set_initials("A");
	        student.set_grades({90, 85, 95});

	        REQUIRE(student.get_surname() == "Smith");
	        REQUIRE(student.get_initials() == "A");
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
	    University::Senior senior("Doe", "J", 3);

	    SECTION("Testing getters and setters") {
	        REQUIRE(senior.get_surname() == "Doe");
	        REQUIRE(senior.get_initials() == "J");
	        REQUIRE(senior.get_grades_num() == 3);

	        senior.set_surname("Smith");
	        senior.set_initials("A");
	        senior.set_grades({90, 85, 95});

	        REQUIRE(senior.get_surname() == "Smith");
	        REQUIRE(senior.get_initials() == "A");
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
	        std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J", 3);
	        std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A", 3);

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
/*
	TEST_CASE("Testing App class") {
		App a;
		SECTION("Add del find group student") {
			std::string s1 = "B22-503", s = "B22-101";
			int n1 = 3, n = 2;
			Group gr1(s1, n1);
			Group gr(s, n);
			a.add_group(gr);
			a.add_group(gr1);
			REQUIRE(a.get_group_num() == 2);
			std::vector<int> m1 = {5, 5, 5}, m2 = {2, 2, 2};
			std::shared_ptr<University::Student> student1 = std::make_shared<University::Student>("Doe", "J", m1, 3);
		    std::shared_ptr<University::Student> student2 = std::make_shared<University::Student>("Smith", "A", m2, 3);
		    gr.add_stud(student1);
		    gr.add_stud(student2);
		    double gpa = a.group_gpa(gr);
		    REQUIRE(gpa == 3.5);
		}
	}
*/	
}
