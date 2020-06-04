#ifndef INTERFACE_QUYENJD_H
#define INTERFACE_QUYENJD_H

#include "csv.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#define Max(a,b) ((a)>(b)?(a):(b))

// overload operator>> (read) for multitype.
// after this operation, multitype always has the type of "str".
std::istream& operator>> (std::istream& in, Csv::multitype& e);

// overload operator<< (write) for multitype.
std::ostream& operator<< (std::ostream& out, const Csv::multitype& e);

// getline for multitype.
void readline (std::istream& in, Csv::multitype& e);

namespace Interface
{
    using namespace Csv;

    // clear the console screen (windows only).
    void clrscr();

    // pause the console screen (windows only).
    void pause();

    // print a note (/w title).
    void print_note (const multitype& note,
                     const multitype& note_head = "No title",
                     bool _clrscr = true,
                     std::ostream& out = std::cout);

    // print a table (/w title).
    void print_table (const table& tabl,
                      const multitype& tabl_head = "No title",
                      bool _nocolumn = true,
                      bool _vertical = true,
                      bool _clrscr = true,
                      std::ostream& out = std::cout);

    // a menu of options of which users select one.
    class select_menu
    {
    private:
        table items;
        multitype title;

    public:
        // constructor.
        select_menu();

        // add an item to the menu.
        void add_item (const int no, const multitype& desc);

        // remove an item from the menu by number.
        bool remove_item_by_no (const int no);

        // set the title of the menu.
        void set_title (const multitype& e);

        // print menu and wait for input.
        // pass false to 'clrscr' if you want to keep the current command lines.
        // this function returns the selected option's No value.
        multitype print_menu_and_wait (bool _clrscr = true, std::ostream& out = std::cout) const;
    };

    // a form of requests where users respond to each.
    class input_menu
    {
    private:
        table items;
        multitype title;

    public:
        // constructor.
        input_menu();

        // add an item to the menu.
        // if line_input is false, the function will use istream::operator>> instead of getline.
        void add_item (const multitype& desc, bool line_input = true);

        // remove an item from the menu by description.
        bool remove_item_by_desc (const multitype& desc, bool strict = false);

        // set the title of the menu.
        void set_title (const multitype& e);

        // print menu and wait for input.
        // pass false to 'clrscr' if you want to keep the current command lines.
        // this function returns the list of input values in the same order as in table.
        list<multitype> print_menu_and_wait (bool _clrscr = true, std::ostream& out = std::cout) const;
    };
}

#endif // INTERFACE_QUYENJD_H
