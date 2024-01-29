#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <thread>
#include <future>

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

    Group &change_sem(Group &gr, std::shared_ptr<Student> &st, int num, std::vector<std::string> topics, int i)
    {
        if (num > gr.get_grnum()) gr.set_grnum(num);
        st->refresh_grades(num);
        int s = gr.get_sem();
        if (s == 3)
        {
            std::shared_ptr<Senior> sen = std::make_shared<Senior>(*st);
            sen->set_topic(topics[i]);
            st = std::static_pointer_cast<Student>(sen);
        }
        return gr;
    }


    Group &App::group_change_sem(Group&& gr, std::vector<int> grnums, std::vector<std::string> topics)
    {
        Table<std::shared_ptr<Student>, std::string> studs = gr.get_studs();
        int i = 0;
        for (auto it = studs.begin(); it != studs.end(); it++)
        {
            if (*it) {gr = change_sem(gr, *it, grnums[i], topics, i); i++;}
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


    void losers(auto start, auto end, std::vector<std::shared_ptr<Student>> &res)
    {
        for (auto it = start; it != end; it++)
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
                if (cnt >= 3)
                    res.push_back(*it_s);
            }
        }
    }

    std::vector <std::shared_ptr<Student>> App::multithread_losers()
    {
        std::vector<std::shared_ptr<Student>> res;
        std::vector<std::future<std::vector<std::shared_ptr<Student>>>> results;
        auto nThreads = std::thread::hardware_concurrency();
        auto dist = std::distance(groups.begin(), groups.end());
        std::mutex mux;
        for (size_t i = 0; i < nThreads; i++)
        {
            size_t start_i = i * dist / nThreads;
            size_t end_i = (i + 1) * dist / nThreads;
            auto start = std::next(groups.begin(), start_i);
            auto end = std::next(groups.begin(), end_i);
            results.push_back(std::async([=, &mux](){
                std::vector<std::shared_ptr<Student>> res;
                losers(start, end, res);
                return res;}));
        }
        for(auto& vecF : results) {
            auto vec = std::move(vecF.get());
            for (size_t i = 0; i < vec.size(); i++)
            {
                res.push_back(vec[i]);
            }
        }

        return res;
    }

    void App::rand_marks()
    {
        for (auto it = groups.begin(); it != groups.end(); it++)
        {
            if (!(*it)) continue;
            Table <std::shared_ptr<Student>, std::string> studs = (*it).get_studs();
            for (auto it_s = studs.begin(); it_s != studs.end(); it_s++)
            {
                if (!(*it_s)) continue;
                std::vector <int> gr((*it_s)->get_grades_num());
                std::random_device r;
                std::generate(gr.begin(), gr.end(), [&]{return r() % 4 + 2;});
                (*it_s)->set_grades(std::move(gr));
            }
        }
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
