#include "scoreboard.h"
#include "interface.h"

Csv::multitype __filter_courseID;
bool __filter_courseID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Course ID")).equal(__filter_courseID);
}

void SMS::view_scoreboard()
{
    Csv::table  scoreboard_table = scoreboard.get_table(),
                courses_table    = courses.get_table();
    int Nrows = courses_table.num_rows();

    Interface::select_menu select;
    select.set_title("Which course do you want to show the scoreboard of?");
    for (int i = 0; i < Nrows; ++i)
        select.add_item(i + 1, courses_table.get_row(i).at(0));
    select.add_item(Nrows + 1, "Back");

    int chosen;
    do
    {
        chosen = select.print_menu_and_wait().to_int();
        if (chosen >= 1 && chosen <= Nrows)
        {
            Csv::multitype courseID = courses_table.get_row(chosen - 1).at(0);
            __filter_courseID.assign(courseID);
            Interface::print_table(scoreboard_table.filter(__filter_courseID_func),
                                   Csv::multitype("Scoreboard of ").append(courseID));
            Interface::pause();
            break;
        }
    }
    while (chosen != Nrows + 1);
}

void SMS::export_scoreboard_to_csv()
{
    Csv::table  scoreboard_table = scoreboard.get_table(),
                courses_table    = courses.get_table();
    int Nrows = courses_table.num_rows();

    Interface::select_menu select;
    select.set_title("Which course do you want to export the scoreboard of?");
    for (int i = 0; i < Nrows; ++i)
        select.add_item(i + 1, courses_table.get_row(i).at(0));
    select.add_item(Nrows + 1, "Back");

    int chosen;
    do
    {
        chosen = select.print_menu_and_wait().to_int();
        if (chosen >= 1 && chosen <= Nrows)
        {
            Csv::multitype courseID = courses_table.get_row(chosen - 1).at(0);
            __filter_courseID.assign(courseID);

            Csv::multitype csv_fname = courseID.append("-Scoreboard.csv");
            Csv::csv_handler out(csv_fname.to_str());
            out.get_table() = scoreboard_table.filter(__filter_courseID_func);
            out.get_table().add_key("Student ID");
            out.get_table().add_key("Course ID");
            out.get_table().add_key("Midterm");
            out.get_table().add_key("Final");
            out.get_table().add_key("Bonus");
            out.get_table().add_key("Total");
            if (!out.init_write())
                return;
            out.write_and_terminate();
            Interface::print_note(Csv::multitype("Exported to ").append(csv_fname).append(" successfully!"),
                                  Csv::multitype("Scoreboard of ").append(courseID));
            Interface::pause();
            break;
        }
    }
    while (chosen != Nrows + 1);
}
