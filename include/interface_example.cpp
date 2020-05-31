#include <iostream>
#include "interface.h"

using namespace std;

int main()
{
    Interface::input_menu menu;
    menu.set_title("Name and Age");
    menu.add_item("Your name", true);
    menu.add_item("Your age", false);
    list<multitype> res = menu.print_menu_and_wait();

    Interface::select_menu menu2;
    menu2.set_title("Increase/Decrease Age");
    menu2.add_item(1, "Increase age by 1");
    menu2.add_item(2, "Decrease age by 1");
    menu2.add_item(3, "Exit");
    int select;
    do
    {
        select = menu2.print_menu_and_wait().to_int();
        switch (select)
        {
        case 1:
        {
            res.at(1).assign(res.at(1).to_int() + 1);
            break;
        }
        case 2:
        {
            res.at(1).assign(res.at(1).to_int() - 1);
            break;
        }
        default:
            break;
        }
    }
    while (select != 3);

    cout << "Name: " << res.at(0) << endl
         << "Age:  " << res.at(1) << endl;
    return 0;
}
