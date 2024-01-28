#include <vector>
#include <string>
#include <thread>

#include "../lib/app.h"

namespace University 
{
    std::string App::key(Group &gr)
    {
        return gr.get_index();
    }

    App::App(std::vector<Group> gr)
    {
        groups = Table<Group, std::string>(gr, key);
    }

    void App::enroll_stud(std::shared_ptr<Student> stud, Group &gr)
    {
    	gr.add_stud(stud);
    }

    double App::group_gpa(Group &gr)
    {
    	double avr_sum = 0;
        int cnt = 0;
        Table <std::shared_ptr<Student>, std::string> studs = gr.get_studs();
    	for (auto it = studs.begin(); it != studs.end(); it++)
    	{
    		if (*it) 
    		{
    			if (!((*it)->get_grades().empty()))
    			{
    				avr_sum += (*it)->get_avr() * (*it)->get_grades_num(); 
    				cnt += (*it)->get_grades_num();
    			}
    		}
    	}
    	if (!cnt) return 0;
    	return (double) avr_sum / cnt;
    }

    Group &App::change_sem(Group &gr, std::shared_ptr<Student> &st, int num)
    {
        if (num > gr.get_grnum()) gr.set_grnum(num);
        st->refresh_grades(num);
        int s = gr.get_sem();
        if (s == 3)
        {
            Junior s = std::move(dynamic_cast<Junior&>(*st));
            std::shared_ptr<Student> sen = std::make_shared<Senior>(dynamic_cast<Student&>(s));
            st = sen;
        }
        return gr;
    }


    Group &App::group_change_sem(Group&& gr, std::vector<int> grnums)
    {
        Table<std::shared_ptr<Student>, std::string> studs = gr.get_studs();
        int i = 0;
        for (auto it = studs.begin(); it != studs.end(); it++)
        {
            if (*it) {gr = change_sem(gr, *it, grnums[i]); i++;}
        }
        gr.set_sem(gr.get_sem() + 1);
        return gr;
    }

    std::vector <std::shared_ptr<Student>> App::find_losers()
    {
    	std::vector<std::shared_ptr<Student>> res;
    	for (auto it = groups.begin(); it != groups.end(); it++)
    	{
            if (!(*it)) continue;
    		Table <std::shared_ptr<Student>, std::string> studs = (*it).get_studs();
    		for (auto it_s = studs.begin(); it_s != studs.end(); it_s++)
    		{
                if (!(*it_s) || (*it_s)->get_grades().empty()) continue;
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

    void group_losers(std::mutex& res_mux, std::vector<std::shared_ptr<Student>> res, std::vector<Group> gr, int start, int end)
    {
        for (int it = start; it < end; it++)
        {
            Table <std::shared_ptr<Student>, std::string> studs = gr[it].get_studs();
            for (auto it_s = studs.begin(); it_s != studs.end(); it_s++)
            {
                if (!(*it_s) || (*it_s)->get_grades().empty()) continue;
                std::vector <int> grades = (*it_s)->get_grades();
                int num = (*it_s)->get_grades_num();
                int cnt = 0;
                for (int i = 0; i < num; i++)
                    if (grades[i] <= 2) cnt++;
                if (cnt >= 3)
                {
                    res_mux.lock();
                    res.push_back(*it_s);
                    res_mux.unlock();
                }
            }
        }
    }

    std::vector <std::shared_ptr<Student>> App::multithread_losers()
    {
        std::vector<std::shared_ptr<Student>> res;
        auto nThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads(nThreads);
        std::vector<Group> gr;
        for (auto it = groups.begin(); it != groups.end(); it++)
        {
            if (*it) gr.push_back(*it);
        }
        int gr_num = groups.get_num();
        std::mutex res_mux;
        for(size_t i = 0; i < nThreads; i++)
        {
            int start = i * gr_num / nThreads;
            int end = (i + 1) * gr_num / nThreads;
            threads[i] = std::thread([=, &res_mux, &res, &gr]() {group_losers(res_mux, res, gr, start, end);});
        }
        for(auto& th : threads)
            th.join();
        return res;
    }

    void App::print_group(std::ostream &c, Group& gr)
    {
        c << gr.get_index() << ":" << std::endl;
    	gr.print(c);
    }

    void App::print(std::ostream &c)
    {
        for (auto it = groups.begin(); it != groups.end(); it++)
        {
            if (!(*it)) continue;
            c << (*it).get_index() << ": " << std::endl;
            (*it).print(c);
        }
    }

    void App::print_with_grades(std::ostream &c)
    {
        for (auto it = groups.begin(); it != groups.end(); it++)
        {
            if (!(*it)) continue;
            c << (*it).get_index() << ": " << std::endl;
            Table <std::shared_ptr<Student>, std::string> studs = (*it).get_studs();
            for (auto it_s = studs.begin(); it_s != studs.end(); it_s++)
            {
                if (!(*it_s)) continue;
                c << (*it_s)->get_surname() << "\n";
                for (int i: (*it_s)->get_grades())
                    c << i << " ";
                c << "\n";
            }
        }
    }
}
