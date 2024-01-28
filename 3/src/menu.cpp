#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>
#include "../lib/app.h"

namespace University
{
    template <typename T>
    void safe_cin(T &var, const char *prompt)
    {
        do {
            std::cout << prompt;
            std::cin >> var;
            if (std::cin.eof())
                throw std::runtime_error("Failed to read value: EOF");
            else if (std::cin.bad())
                throw std::runtime_error(std::string("Failed to read value: ") + std::strerror(errno));
            else if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong, repeat please!" << std::endl;
            }
            else if (std::cin.good())
                return;
        } while (true);
    }

    int menu(const char *opts[], int num_opts)
    {
        int var = 0;
        do {
            if (var >= num_opts || var < 0) std::cout << "Error! Number must be in range of options. Try again..." << std::endl;
            for (int i = 0; i < num_opts; i++)
                std::cout << opts[i] << std::endl;
            safe_cin<int>(var, "Choose option: ");
        } while (var >= num_opts || var < 0);

        return var;
    }

    void dlg_read_file(App& a)
    {
        std::ifstream fdata;
        std::string fname;
        safe_cin<std::string>(fname, "Write name of file: ");
        fdata.open(fname);
        if(!fdata)
            throw::std::runtime_error("Failed to open the file.");
        std::string ind, name, ins;
        int sem, num, gr_num;
        fdata >> ind;
        while (!fdata.eof())
        {
            fdata >> sem;
            Group gr(ind, sem);
            fdata >> num;
            for (int i = 0; i < num; i++)
            {
                std::shared_ptr<Student> st_p;
                fdata >> name;
                fdata >> ins;
                fdata >> gr_num;
                if (sem < 4)
                    st_p = std::make_shared<Junior>(name, ins, gr_num);
                else
                    st_p = std::make_shared<Senior>(name, ins, gr_num);
                gr.add_stud(st_p);
            }
            a.add_group(gr);
            fdata >> ind;
        }
    }
    void dlg_marks(App &a)
    {
        std::string ind, name;
        int num_g, num_s;
        do {
            safe_cin<int>(num_g, "How many groups would you like to enter: ");
        } while(num_g <= 0);
        for (int j = 0; j < num_g || std::cin.eof(); j++)
        {
            safe_cin<std::string>(ind, "Write group index: ");
            try
            {
                Group gr = a.find_group(ind);
                std::cout << "Number of students in " << ind << " = " << gr.get_num() << std::endl;
                do {
                    safe_cin<int>(num_s, "How many students would you like to enter: ");
                } while(num_s <= 0 || num_s > gr.get_num());
                std::cout << "Here are the students' surnames: " << std::endl;
                gr.print(std::cout);
                for (int i = 0; i < num_s || std::cin.eof(); i++)
                {
                    safe_cin<std::string>(name, "Write student surname: ");
                    try
                    {
                        std::shared_ptr<Student> st = gr.find_stud(name);
                        int g_num = st->get_grades_num(), n;
                        std::cout << "Enter grades (" << g_num << "): ";
                        std::vector<int> grades;
                        for (int k = 0; k < g_num; k++)
                        {
                            std::cin >> n;
                            grades.push_back(n);
                        }
                        st->set_grades(grades);
                    }
                    catch(const std::invalid_argument& e)
                    {
                        std::cout << "There is no such student. Try again . . ." << std::endl;
                        i--;
                    }
                }
            }
            catch(const std::invalid_argument& e)
            {
                std::cout << "There is no such group. Try again . . ." << std::endl;
                j--;
            }
        }
    }
    void dlg_sheet(App &a)
    {
        std::ofstream fdata;
        fdata.open("../etc/marks.txt");
        if(!fdata)
            throw::std::runtime_error("Failed to open the file.");
        a.print_with_grades(fdata);
        std::cout << "Sheet of marks of all groups is now in etc/marks.txt!" << std::endl;
    }

    void stud_add(Group &&gr, int num)
    {
        int sem = gr.get_sem();
        for (int i = 0; i < num; i++)
        {
            std::shared_ptr<Student> st_p;
            std::string name, ins;
            int gr_num;
            std::cout << "Write surname and initials (separate with space): ";
            std::cin >> name;
            if (std::cin.eof()) throw std::runtime_error("Failed to read value: EOF");
            std::cin >> ins;
            if (std::cin.eof()) throw std::runtime_error("Failed to read value: EOF");
            do {
                safe_cin<int>(gr_num, "Write number of grades: ");
            } while (gr_num <= 0);
            if (sem < 4) st_p = std::make_shared<Junior>(name, ins, gr_num);
            else st_p = std::make_shared<Senior>(name, ins, gr_num);
            gr.add_stud(st_p);
        }
    }

    Group &dlg_find(App &a)
    {
        std::string ind;
        safe_cin<std::string>(ind, "Write index of the group: ");
        return a.find_group(ind);
    }

    void dlg_add_group(App &a)
    {
        std::string ind;
        int sem;
        bool b;
        safe_cin<std::string>(ind, "Write index of the group: ");
        safe_cin<int>(sem, "Write semester of the group: ");
        Group gr(ind, sem);
        std::cout << "Would you like to add students? (1/0) ";
        std::cin >> b;
        if (b)
        {
            int num;
            do {
                safe_cin<int>(num, "How many students would you like to enter? ");
            } while (num <= 0);
            stud_add(std::move(gr), num);
        }
        a.add_group(gr);
    }

    void dlg_add_studs(App &a)
    {
        int num;
        do {
            safe_cin<int>(num, "How many students would you like to enter? ");
        } while (num <= 0);
        stud_add(std::move(dlg_find(a)), num);
    }

    void dlg_add_stud(App &a)
    {
        stud_add(std::move(dlg_find(a)), 1);
    }

    void dlg_gpa_group(App &a)
    {
        Group gr = dlg_find(a);
        double gpa = a.group_gpa(gr);
        std::cout << "GPA of " << gr.get_index() << " group is " << gpa << std::endl;
    }

    void dlg_print_group(App &a)
    {
        a.print_group(std::cout, dlg_find(a));
    }

    void dlg_print_groups(App &a)
    {
        a.print(std::cout);
    }

    void dlg_change_sem(App &a)
    {
        Group gr = dlg_find(a);
    }

    void dlg_losers(App &a)
    {
        std::cout << "Here are the losers, students with 3 or more F's:";
        std::vector<std::shared_ptr<Student>> losers = a.find_losers();
        if (losers.empty()) std::cout << " there is no.";
        for (auto & loser : losers)
            std::cout << " " << loser->get_surname();
        std::cout << std::endl;
    }
}
