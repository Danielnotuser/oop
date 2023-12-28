#include <vector>
#include <string>

#include "../lib/app.h"
#include "../lib/table.h"
#include "../lib/group.h"
#include "../lib/stud.h"

namespace University 
{
    std::string group_index(Group gr)
    {
        return gr.get_index();
    }

    App::App(std::vector<Group> gr)
    {
        groups = Table<Group>(gr, &group_index);
    }

    void App::enroll_stud(std::shared_ptr<Student> stud, std::string group_index)
    {
    	Group a = groups.find(group_index);
    	a.add_stud(stud);
    }

    double App::gpa(Group gr)
    {
    	double avr_sum = 0;
        Table <std::shared_ptr<Student>> studs = gr.get_studs();
    	for (auto it = studs.begin(); it != studs.end(); it++)
    	{
    		avr_sum += (*it)->get_avr();
    	}
    	return (double) avr_sum / studs.get_num();
    }

    std::vector <std::shared_ptr<Student>> find_losers()
    {
    	std::vector<std::shared_ptr<Student>> res;
    	for (auto it = groups.begin(); it != groups.end(); it++)
    	{
    		Table <std::shared_ptr<Student>> studs = (*it).get_studs();
    		for (auto it_s = studs.begin(); it_s != studs.end(); it++)
    		{
    			std::vector <int> grades = (*it_s)->get_grades();
    			int num = (*it_s)->get_grades_num();
    			int cnt = 0;
    			for (int i = 0; i < num; i++)
    				if (grades[i] <= 2) cnt++;
    			if (cnt >= 3) res.push_back(*it_s);  
    		}
    	}
    	return res;
    }

    void App::print_group(std::string index)
    {
    	Group gr = groups.find(index);
    	gr.print();
    }
}
