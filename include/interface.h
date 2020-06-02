#ifndef INTERFACE_QUYENJD_H
#define INTERFACE_QUYENJD_H

#include "csv.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#define Max(a,b) ((a)>(b)?(a):(b))

// overload operator>> (read) for multitype.
// after this operation, multitype always has the type of "str".
extern std::istream& operator>> (std::istream& in, Csv::multitype& e);

// overload operator<< (write) for multitype.
extern std::ostream& operator<< (std::ostream& out, const Csv::multitype& e);

// getline for multitype.
extern void readline (std::istream& in, Csv::multitype& e);

namespace Interface
{
    using namespace Csv;

    extern void print_table (const table& Table,
                             const multitype& Table_head = "No title",
                             bool clrscr = true,
                             std::ostream& out = std::cout);

    class select_menu
    {
    private:
        table items;
        multitype title;

    public:
        // constructor.
        select_menu()
        {
            items.add_key("No");
            items.add_key("Description");
            title.assign("No title");
        }

        // add an item to the menu.
        void add_item (const int no, const multitype& desc)
        {
            items.add_row();
            items.get(items.num_rows() - 1, "No").assign(no);
            items.get(items.num_rows() - 1, "Description").assign(desc);
        }

        // remove an item from the menu by number.
        bool remove_item_by_no (const int no)
        {
            return items.rm_row_where("No", no);
        }

        // set the title of the menu.
        void set_title (const multitype& e)
        {
            title = e;
        }

        // print menu and wait for input.
        // pass false to 'clrscr' if you want to keep the current command lines.
        // this function returns the selected option's No value.
        multitype print_menu_and_wait (bool clrscr = true, std::ostream& out = std::cout) const
        {
            if (clrscr)
                system("cls"); // windows only
            out << "[ SELECT: " << title << " ]" << std::endl
                << "____" << std::endl
                << std::endl;

            int maxl = 0;
            for (int i = 0; i < items.num_rows(); ++i)
                maxl = Max(maxl, (int)strlen(items.get(i, "No").to_str()));
            for (int i = 0; i < items.num_rows(); ++i)
            {
                out << "  " << items.get(i, "No") << ". ";
                for (int j = 0; j < maxl - (int)strlen(items.get(i, "No").to_str()); ++j)
                    out << " ";
                out << items.get(i, "Description") << std::endl;
            }
            out << "____" << std::endl;

            // wait for user to choose
            while (true)
            {
                out << std::endl
                    << "Your choice: ";
                multitype choice; std::cin >> choice;
                if (!items.get_where("No", choice, "No").equal("bad_access"))
                {
                    out << std::endl;
                    return choice;
                }
            }
        }
    };

    class input_menu
    {
    private:
        table items;
        multitype title;

    public:
        // constructor.
        input_menu()
        {
            items.add_key("Description");
            items.add_key("Line input");
            title.assign("No title");
        }

        // add an item to the menu.
        void add_item (const multitype& desc, bool line_input)
        {
            if (!items.get_where("Description", desc, "Description").equal("bad_access"))
                return;
            items.add_row();
            items.get(items.num_rows() - 1, "Description").assign(desc);
            items.get(items.num_rows() - 1, "Line input").assign((int)line_input);
        }

        // remove an item from the menu by description.
        bool remove_item_by_desc (const multitype& desc, bool strict = false)
        {
            return items.rm_row_where("Description", desc, strict);
        }

        // set the title of the menu.
        void set_title (const multitype& e)
        {
            title = e;
        }

        // print menu and wait for input.
        // pass false to 'clrscr' if you want to keep the current command lines.
        // this function returns the list of input values in the same order as in table.
        list<multitype> print_menu_and_wait (bool clrscr = true, std::ostream& out = std::cout) const
        {
            if (clrscr)
                system("cls"); // windows only
            out << "[ INPUT: " << title << " ]" << std::endl
                << "____" << std::endl
                << std::endl;

            list<multitype> res;
            int maxl = 0;
            for (int i = 0; i < items.num_rows(); ++i)
                maxl = Max(maxl, (int)strlen(items.get(i, "Description").to_str()));
            for (int i = 0; i < items.num_rows(); ++i)
            {
                multitype e;
                out << "  " << items.get(i, "Description") << "  ";
                for (int j = 0; j < maxl - (int)strlen(items.get(i, "Description").to_str()); ++j)
                    out << " ";
                if (items.get(i, "Line input").to_int())
                    readline(std::cin, e);
                else
                    std::cin >> e;
                res.push_back(e);
            }
            out << "____" << std::endl
                << std::endl;

            return res;
        }
    };
}

#endif // INTERFACE_QUYENJD_H
