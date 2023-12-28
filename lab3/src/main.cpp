#include <iostream>
#include <string>
#include <vector>


void Dialogue()
{
	std::string menu = {"0. Quit\n1. Add Group\n2. Add list of student to the group.\n3. Add student to the group\n
						 4. Print gpa for the group\n5. Print group\n6. Print group list\n7. Change semester for student.\n
						 8. Print losers"};
	std::cout << "Menu:" << std::endl;
	std::cout << "0. Quit" << std::endl;	
}

int main()
{
	Dialogue();
	return 0;
}
