#include <iostream>
#include <compare>
#include "card.h"

void menu()
{
    std::cout << "Select item from this menu:" << std::endl;
    std::cout << "\t0. Quit" << std::endl;
    std::cout << "\t1. Initialise Card with random." << std::endl;
    std::cout << "\t2. Initialise Card with your values." << std::endl;
    std::cout << "\t3. Set Card fields." << std::endl;
    std::cout << "\t4. Get rank." << std::endl;
    std::cout << "\t5. Get suit." << std::endl;
    std::cout << "\t6. Compare with previous." << std::endl;
    std::cout << "\t7. Print card." << std::endl;
}


int main()
{
    int n;
    while (true)
    {
        menu();
        std::cout << "Enter menu item: ";
        std::cin >> n;

    }
    return 0;
}