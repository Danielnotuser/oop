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
        groups = Table<Group>(gr, group_index);
    }

    void App::enroll_stud(Student *stud, std::string group_index)
    {
    	Group a = groups.find(group_index);
    	a.add_stud(stud);
    }

    double App::gpa(Group gr)
    {
    	double avr_sum = 0;
    	for (auto it = gr.studs.begin(); it < gr.studs.end(); it++)
    	{
    		avr_sum += (*it)->get_avr();
    	}
    	return (double) avr_sum / gr.studs.get_num();
    }
}
