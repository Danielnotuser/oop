#include <vector>
#include <string>

#include "app.h"
#include "table.h"
#include "group.h"
#include "student.h"

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
