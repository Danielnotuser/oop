#ifndef MENU_H
#define MENU_H

#include "app.h"

namespace University
{
    int menu(const char *opts[], int);
    void dlg_read_file(App&);
    void dlg_add_group(App&);
    void dlg_add_studs(App&);
    void dlg_add_stud(App&);
    void dlg_gpa_group(App&);
    void dlg_print_group(App&);
    void dlg_print_groups(App&);
    void dlg_change_sem(App&);
    void dlg_losers(App&);
    void dlg_sheet(App&);
}

#endif
