#include <vector>
#include <string>

#include "../lib/app.h"
#include "../lib/table.h"
#include "../lib/group.h"
#include "../lib/stud.h"

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
}
