#include <iostream>
#include <vector>
#include "../lib/app.h"
#include "../lib/menu.h"

using namespace University;

int main()
{
    int var, num_opts = 11;
    App my_app;
    const char *opts[] = {"0. Quit","1. Read groups from file.","2. Add Group","3. Add list of student to the group.",
                          "4. Add student to the group","5. Print gpa for the group","6. Print group",
                          "7. Print list of groups","8. Change semester for the student.","9. Print losers","10. Create mark sheet."};
    void (*fptr[])(App&) = {dlg_read_file, dlg_add_group, dlg_add_stud, dlg_add_studs, dlg_gpa_group, dlg_print_group, dlg_print_groups, dlg_change_sem, dlg_losers, dlg_sheet};
    while ((var = menu(opts, num_opts)))
    {
        try
        {
            fptr[var-1](my_app);
        }
        catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "See you later!";
	return 0;
}
