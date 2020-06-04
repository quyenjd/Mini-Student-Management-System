#include "lecturer.h"
#include "csv_import.h"
#include "csv.h"
#include "interface.h"

Csv::multitype __courselecturer_filter_courseID;
bool __courselecturer_filter_courseID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return column.equal("Username") && row.at(tabl.get_key("Course ID")).equal(__courselecturer_filter_courseID);
}

Csv::list<Csv::multitype> __lecturers_filter_lecturerIDs;
bool __lecturers_filter_lecturerIDs_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    for (int i = 0; i < __lecturers_filter_lecturerIDs.size(); ++i)
        if (row.at(tabl.get_key("Username")).equal(__lecturers_filter_lecturerIDs.at(i)))
            return true;
    return false;
}

namespace SMS
{
    void add_lecturer()
    {
        Interface::input_menu input;
        input.set_title("Add new lecturer");
        input.add_item("Username");
        input.add_item("Name");
        input.add_item("Degree");
        input.add_item("Gender");
        Csv::list<Csv::multitype> res = input.print_menu_and_wait();

        Csv::table &lecturer_table = lecturers.get_table();
        int Nrows = lecturer_table.num_rows();

        bool flag = false;
        for (int i = 0; i < Nrows; ++i)
            if (lecturer_table.get(i, "Username").equal(res.at(0)))
                flag = true;
        if (flag)
        {
            Interface::print_note("Duplicate lecturer's username detected. Please try again", "Failed");
            Interface::pause();
            return;
        }

        lecturer_table.add_row();
        lecturer_table.get(Nrows, "Username").assign(res.at(0));
        lecturer_table.get(Nrows, "Name").assign(res.at(1));
        lecturer_table.get(Nrows, "Degree").assign(res.at(2));
        lecturer_table.get(Nrows, "Gender").assign(res.at(3));

        if (!lecturers.init_write())
            return;
        lecturers.write_and_terminate();

        // Add new lecturer to table 'users'
        users.get_table().add_row();
        users.get_table().get(users.get_table().num_rows() - 1, "ID").assign(res.at(0));
        users.get_table().get(users.get_table().num_rows() - 1, "Pass").assign(res.at(0));
        users.get_table().get(users.get_table().num_rows() - 1, "Role").assign("Lecturer");

        if (!users.init_write())
            return;
        users.write_and_terminate();

        Interface::print_note("Added new lecturer successfully!", "Success");
        Interface::pause();
    }

    void edit_lecturer()
    {
        Csv::table &lecturer_table = lecturers.get_table();
        int Nrows = lecturer_table.num_rows();

        Interface::print_table(lecturer_table, "Lecturers", false);

        Interface::input_menu input;
        input.set_title("Which lecturer do you want to edit the information of?");
        input.add_item("Lecturer's username");

        Csv::multitype lecturerID = input.print_menu_and_wait(false).at(0);
        bool flag = false;
        for (int i = 0; i < Nrows; ++i)
            if (lecturer_table.get(i, "Username").equal(lecturerID))
                flag = true;
        if (!flag)
        {
            Interface::print_note(Csv::multitype("No lecturer with ID:").append(lecturerID).append(" is found."), "Failed");
            Interface::pause();
            return;
        }

        Interface::input_menu input2;
        input2.set_title(Csv::multitype("Editing lecturer:").append(lecturerID));
        input2.add_item("New name");
        input2.add_item("New degree");
        input2.add_item("New gender");
        Csv::list<Csv::multitype> res = input2.print_menu_and_wait();

        lecturer_table.get_where("Username", lecturerID, "Name").assign(res.at(0));
        lecturer_table.get_where("Username", lecturerID, "Degree").assign(res.at(1));
        lecturer_table.get_where("Username", lecturerID, "Gender").assign(res.at(2));

        if (!lecturers.init_write())
            return;
        lecturers.write_and_terminate();

        Interface::print_note(Csv::multitype("Information of lecturer:").append(lecturerID).append(" has been updated successfully!"),
                              "Success");
        Interface::pause();
    }

    void delete_lecturer()
    {
        Csv::table &lecturer_table = lecturers.get_table();
        int Nrows = lecturer_table.num_rows();

        Interface::print_table(lecturer_table, "Lecturers", false);

        Interface::input_menu input;
        input.set_title("Which lecturer do you want to remove?");
        input.add_item("Lecturer's username");

        Csv::multitype lecturerID = input.print_menu_and_wait(false).at(0);
        bool flag = false;
        for (int i = 0; i < Nrows; ++i)
            if (lecturer_table.get(i, "Username").equal(lecturerID))
                flag = true;
        if (!flag)
        {
            Interface::print_note(Csv::multitype("No lecturer with ID:").append(lecturerID).append(" is found."), "Failed");
            Interface::pause();
            return;
        }

        lecturer_table.rm_row_where("Username", lecturerID);
        if (!lecturers.init_write())
            return;
        lecturers.write_and_terminate();

        Interface::print_note(Csv::multitype("Lecturer:").append(lecturerID).append(" has been removed successfully!"),
                              "Success");
        Interface::pause();
    }

    void view_all_lecturers()
    {
        Interface::print_table(lecturers.get_table(), "Lecturers");
        Interface::pause();
    }

    void view_lecturers_of_course()
    {
        Csv::table  course_table = courses.get_table();
        int Nrows = course_table.num_rows();

        Interface::select_menu select;
        select.set_title("Courses");
        for (int i = 0; i < Nrows;i++)
            select.add_item(i + 1, course_table.get_row(i).at(0));
        select.add_item(Nrows + 1,"Back");

        int chosen;
        do
        {
            chosen = select.print_menu_and_wait().to_int();
            if (chosen >=1 && chosen <= Nrows)
            {
                Csv::multitype courseID = course_table.get_row(chosen - 1).at(0);
                __courselecturer_filter_courseID.assign(courseID);
                Csv::table courselecturer_table = courselecturer.get_table().filter(__courselecturer_filter_courseID_func);

                __lecturers_filter_lecturerIDs.destroy();
                for (int i = 0; i < courselecturer_table.num_rows(); ++i)
                    __lecturers_filter_lecturerIDs.push_back(courselecturer_table.get_row(i).at(0));

                Interface::print_table(lecturers.get_table().filter(__lecturers_filter_lecturerIDs_func),
                                       multitype("List of lecturers in ").append(courseID));
                Interface::pause();
            }

        }
        while (chosen != Nrows + 1);
    }
}
