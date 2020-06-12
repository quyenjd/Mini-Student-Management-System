#include "scoreboard.h"
#include "interface.h"
#include "csv_import.h"

Csv::multitype __scoreboard_filter_courseID;
bool __scoreboard_filter_courseID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Course ID")).equal(__scoreboard_filter_courseID);
}

Csv::multitype __courses_filter_studentID;
bool __courses_filter_studentID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Student ID")).equal(__courses_filter_studentID);
}

bool __scoreboard_filter_courseID_studentID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Course ID")).equal(__scoreboard_filter_courseID) &&
           row.at(tabl.get_key("Student ID")).equal(__courses_filter_studentID);
}

namespace SMS
{
    void import_scoreboard()
    {
        Csv::table &scoreboard_table = scoreboard.get_table(),
                    courses_table = courses.get_table();
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to import the scoreboard to?");
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
                Interface::input_menu input;
                input.set_title("File Information");
                input.add_item("Your csv (Student ID, Midterm, Final, Bonus, Total) file name");

                Csv::multitype csv_fname = input.print_menu_and_wait().at(0);
                Csv::csv_handler csv(csv_fname.to_str());
                if (!csv.init_read())
                {
                    Interface::print_note(Csv::multitype("Your file '").append(csv_fname).append("' is corrupted. Please try again."), "Failed");
                    Interface::pause();
                    break;
                }
                csv.read_and_terminate();
                csv.get_table().fix_keys({"Student ID", "Midterm", "Final", "Bonus", "Total"});
                for (int i = 0; i < csv.get_table().num_rows(); ++i)
                {
                    scoreboard_table.add_row();
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(0) = csv.get_table().get_row(i).at(0);
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(1) = courseID;
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(2) = csv.get_table().get_row(i).at(1);
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(3) = csv.get_table().get_row(i).at(2);
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(4) = csv.get_table().get_row(i).at(3);
                    scoreboard_table.get_row(scoreboard_table.num_rows() - 1).at(5) = csv.get_table().get_row(i).at(4);
                }
                if (!scoreboard.init_write())
                    break;
                scoreboard.write_and_terminate();
                Interface::print_note(Csv::multitype("Imported from ").append(csv_fname).append(" successfully!"),
                                      Csv::multitype("Import to ").append(courseID).append("'s scoreboard"));
                Interface::pause();
            }
        }
        while (chosen != Nrows + 1);
    }

    void edit_scoreboard()
    {
        Csv::table &scoreboard_table = scoreboard.get_table(),
                    courses_table = courses.get_table();
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to edit the scoreboard of?");
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
                __scoreboard_filter_courseID.assign(courseID);
                Interface::print_table(scoreboard_table.filter(__scoreboard_filter_courseID_func),
                                       Csv::multitype("Scoreboard of ").append(courseID), false);

                Interface::input_menu input;
                input.set_title("Which student do you want to edit the grades of?");
                input.add_item("Student ID");
                Csv::multitype studentID = input.print_menu_and_wait(false).at(0);
                __courses_filter_studentID.assign(studentID);
                if (scoreboard_table.filter(__scoreboard_filter_courseID_studentID_func).num_rows() > 0)
                {
                    Interface::input_menu input2;
                    input2.set_title(Csv::multitype("New grades for ").append(studentID));
                    input2.add_item("Midterm");
                    input2.add_item("Final");
                    input2.add_item("Bonus");
                    input2.add_item("Total");
                    Csv::list<Csv::multitype> res = input2.print_menu_and_wait();

                    for (int i = 0; i < scoreboard_table.num_rows(); ++i)
                        if (scoreboard_table.get(i, "Course ID").equal(courseID) &&
                            scoreboard_table.get(i, "Student ID").equal(studentID))
                        {
                            scoreboard_table.get_row(i).at(2) = res.at(0);
                            scoreboard_table.get_row(i).at(3) = res.at(1);
                            scoreboard_table.get_row(i).at(4) = res.at(2);
                            scoreboard_table.get_row(i).at(5) = res.at(3);
                        }
                }
                else
                {
                    Interface::print_note(Csv::multitype("No student with ID:").append(studentID).append(" is found in ").
                                          append(courseID).append("'s scoreboard."), "Invalid student");
                    Interface::pause();
                }
            }
        }
        while (chosen != Nrows + 1);
    }

    void view_scoreboard()
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
                __scoreboard_filter_courseID.assign(courseID);
                Interface::print_table(scoreboard_table.filter(__scoreboard_filter_courseID_func),
                                       Csv::multitype("Scoreboard of ").append(courseID));
                Interface::pause();
            }
        }
        while (chosen != Nrows + 1);
    }

    void student_view_scoreboard (const Csv::multitype& studentID)
    {
        __courses_filter_studentID.assign(studentID);
        Csv::table  scoreboard_table = scoreboard.get_table(),
                    coursestudent_table = coursestudent.get_table().filter(__courses_filter_studentID_func);
        int Nrows = coursestudent_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to show the scoreboard of?");
        for (int i = 0; i < Nrows; ++i)
            select.add_item(i + 1, coursestudent_table.get_row(i).at(0));
        select.add_item(Nrows + 1, "Back");

        int chosen;
        do
        {
            chosen = select.print_menu_and_wait().to_int();
            if (chosen >= 1 && chosen <= Nrows)
            {
                Csv::multitype courseID = coursestudent_table.get_row(chosen - 1).at(0);
                __scoreboard_filter_courseID.assign(courseID);
                Interface::print_table(scoreboard_table.filter(__scoreboard_filter_courseID_studentID_func),
                                       Csv::multitype(studentID).append("'s scoreboard of ").append(courseID));
                Interface::pause();
            }
        }
        while (chosen != Nrows + 1);
    }

    void export_scoreboard_to_csv()
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
                __scoreboard_filter_courseID.assign(courseID);

                Csv::multitype csv_fname = courseID.append("-Scoreboard.csv");
                Csv::csv_handler out(csv_fname.to_str());
                out.get_table() = scoreboard_table.filter(__scoreboard_filter_courseID_func);
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
            }
        }
        while (chosen != Nrows + 1);
    }
}
