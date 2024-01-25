#include <vector>
#include <string>

#include "../lib/app.h"

namespace University 
{
    std::string group_index(Group &gr)
    {
        return gr.get_index();
    }

    App::App(std::vector<Group> gr)
    {
        groups = Table<Group, std::string>(gr, group_index);
    }

    void App::enroll_stud(std::shared_ptr<Student> stud, Group &gr)
    {
    	gr.add_stud(stud);
    }

    double App::gpa(Group &gr)
    {
    	double avr_sum = 0;
        Table <std::shared_ptr<Student>, std::string> studs = gr.get_studs();
    	for (auto it = studs.begin(); it != studs.end(); it++)
    	{
    		avr_sum += (*it)->get_avr();
    	}
    	return (double) avr_sum / studs.get_num();
    }
   /* void App::change_sem(Group &gr, std::shared_ptr<Student> st, int num)
    {
        if (num > gr.get_grnum()) gr.set_grnum(num);
        st->refresh_grades(num);
        int s = gr.get_sem();
        if (s == 3)
        {
            Senior s(*st);
            st = dynamic_cast<Student*>(&s);
            std::shared_ptr<Student> sen = dynamic_cast<Senior&>(*st);
            Senior s(dynamic_cast<Senior&>(*st));
        }
        else if (s < 8)
            gr.set_sem(s + 1);
        else
            groups.del(gr.get_index());
        // dynamic cast . . .
    }*/

    std::vector <std::shared_ptr<Student>> App::find_losers()
    {
    	std::vector<std::shared_ptr<Student>> res;
    	for (auto it = groups.begin(); it != groups.end(); it++)
    	{
    		Table <std::shared_ptr<Student>, std::string> studs = (*it).get_studs();
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

    void App::print_group(std::ostream &c, Group& gr)
    {
    	gr.print(c);
    }

    void App::print(std::ostream &c)
    {
        for (auto it = groups.begin(); it != groups.end(); it++)
        {
            c << (*it).get_index() << ": ";
            (*it).print(c);
        }
    }

    void App::print_with_grades(std::ostream &c)
    {
        for (auto it_g = groups.begin(); it_g != groups.end(); it_g++)
        {
            c << (*it_g).get_index() << ": ";
            Table <std::shared_ptr<Student>, std::string> studs = (*it_g).get_studs();
            for (auto it_s = studs.begin(); it_s != studs.end(); it_s++)
            {
                c << (*it_s)->get_surname() << "\n";
                for (int i: (*it_s)->get_grades())
                    c << i << " ";
                c << "\n";
            }
        }
    }
}
