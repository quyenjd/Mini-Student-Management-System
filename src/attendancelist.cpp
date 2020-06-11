#include "attendancelist.h"
#include "interface.h"
#include "csv_import.h"
#include "date.h"

Csv::multitype __attendancelist_filter_courseID;
bool __attendancelist_filter_courseID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Course ID")).equal(__attendancelist_filter_courseID);
}

Csv::multitype __attendancelist_filter_studentID;
bool __attendancelist_filter_studentID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return row.at(tabl.get_key("Student ID")).equal(__attendancelist_filter_studentID);
}
bool __attendancelist_filter_studentID_view_mode_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    return !column.equal("Attendance ID") && !column.equal("Student ID") &&
           row.at(tabl.get_key("Student ID")).equal(__attendancelist_filter_studentID);
}

bool __attendancelist_filter_studentID_checkin_courseID_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    if (!row.at(tabl.get_key("Course ID")).equal(__attendancelist_filter_courseID) ||
        !row.at(tabl.get_key("Student ID")).equal(__attendancelist_filter_studentID))
        return false;
    date tnow, checkin_date;
    tnow.now();
    checkin_date.parse(row.at(tabl.get_key("Checkin at")), "YYYY/MM/DD hh:mm");
    return tnow.substract(checkin_date) < 1;
}

Csv::list<Csv::multitype> __courses_filter_valid_courseIDs;
bool __courses_filter_date_func (Csv::multitype column, Csv::list<Csv::multitype> row, Csv::table tabl)
{
    if (!column.equal("Course ID") && !column.equal("Start hour") && !column.equal("Start minute") &&
        !column.equal("End hour") && !column.equal("End minute"))
        return false;

    Csv::multitype courseID = row.at(0);
    bool flag = false;
    for (int i = 0; i < __courses_filter_valid_courseIDs.size(); ++i)
        if (courseID.equal(__courses_filter_valid_courseIDs.at(i)))
            flag = true;
    if (!flag)
        return false;

    date tnow, st_date, en_date;
    tnow.now();
    st_date.parse(row.at(tabl.get_key("Start date")), "YYYY/MM/DD");
    en_date.parse(row.at(tabl.get_key("End date")), "YYYY/MM/DD");

    if (tnow < st_date || tnow > en_date)
        return false;

    st_date = en_date = tnow;
    st_date.hour = row.at(tabl.get_key("Start hour")).to_int();
    st_date.minute = row.at(tabl.get_key("Start minute")).to_int();
    en_date.hour = row.at(tabl.get_key("End hour")).to_int();
    en_date.minute = row.at(tabl.get_key("End minute")).to_int();

    static Csv::multitype dows[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    Csv::multitype dow = row.at(tabl.get_key("Day of week"));
    for (int i = 0; i < 7; ++i)
        if (dows[i].equal(dow) && tnow.wday == i && tnow >= st_date && tnow <= en_date)
            return true;
    return false;
}

namespace SMS
{
    void view_attendance_list()
    {
        Csv::table  attendance_table = attendancelist.get_table(),
                    courses_table    = courses.get_table();
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to show the attendance list of?");
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
                __attendancelist_filter_courseID.assign(courseID);
                Interface::print_table(attendance_table.filter(__attendancelist_filter_courseID_func),
                                       Csv::multitype("Attendance list of ").append(courseID),
                                       false);
                Interface::pause();
            }
        }
        while (chosen != Nrows + 1);
    }

    void export_attendance_list_to_csv()
    {
        Csv::table  attendance_table = attendancelist.get_table(),
                    courses_table    = courses.get_table();
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to export the attendance list of?");
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
                __attendancelist_filter_courseID.assign(courseID);

                Csv::multitype csv_fname = courseID.append("-AttendanceList.csv");
                Csv::csv_handler out(csv_fname.to_str());
                out.get_table() = attendance_table.filter(__attendancelist_filter_courseID_func);
                out.get_table().add_key("Attendance ID");
                out.get_table().add_key("Student ID");
                out.get_table().add_key("Course ID");
                out.get_table().add_key("Checkin at");
                out.get_table().add_key("Active");
                if (!out.init_write())
                    return;
                out.write_and_terminate();
                Interface::print_note(Csv::multitype("Exported to ").append(csv_fname).append(" successfully!"),
                                      Csv::multitype("Attendance list of ").append(courseID));
                Interface::pause();
            }
        }
        while (chosen != Nrows + 1);
    }

    void edit_attendance_table (const Csv::table& tabl)
    {
        Interface::print_table(tabl, "Attendance list", false);
        Interface::input_menu input;
        input.set_title("Choose attendance ID");
        input.add_item("Attendance ID");
        Csv::list<Csv::multitype> res = input.print_menu_and_wait(false);

        Csv::list<Csv::multitype> &row = attendancelist.get_table().get_row_where("Attendance ID", res.at(0));
        if (row.empty())
        {
            Interface::print_note(Csv::multitype("No attendance with ID:").append(res.at(0)).append(" is found."),
                                  "Attendance not found");
            Interface::pause();
            return;
        }
        else
        {
            Interface::select_menu select;
            select.set_title("Edit attendance");
            select.add_item(1, "Change active state");
            select.add_item(2, "Delete");
            select.add_item(3, "Back");

            int chosen;
            while (true)
            {
                chosen = select.print_menu_and_wait().to_int();
                if (chosen == 1)
                {
                    Csv::multitype &active = attendancelist.get_table().get_where("Attendance ID", res.at(0), "Active");
                    active = !active.to_int();
                    if (!attendancelist.init_write())
                        break;
                    attendancelist.write_and_terminate();
                    Interface::print_note(Csv::multitype("Changed the attendance's state to ").append(active),
                                          "Edit attendance");
                    Interface::pause();
                }
                else
                if (chosen == 2)
                {
                    attendancelist.get_table().rm_row_where("Attendance ID", res.at(0));
                    if (!attendancelist.init_write())
                        break;
                    attendancelist.write_and_terminate();
                    Interface::print_note("Successfully deleted the attendance.", "Edit attendance");
                    Interface::pause();
                }
                break;
            }
        }
    }

    void edit_attendance_by_course()
    {
        Csv::table &attendance_table = attendancelist.get_table(),
                    courses_table    = courses.get_table();
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title("Which course do you want to edit the attendance list of?");
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
                __attendancelist_filter_courseID.assign(courseID);
                edit_attendance_table(attendance_table.filter(__attendancelist_filter_courseID_func));
            }
        }
        while (chosen != Nrows + 1);
    }

    void edit_attendance_by_student()
    {
        Csv::table &attendance_table = attendancelist.get_table();

        Interface::input_menu input;
        input.set_title("Which student do you want to edit the attendance list of?");
        input.add_item("Student ID");

        Csv::multitype studentID = input.print_menu_and_wait().at(0);
        if (students.get_table().get_row_where("Student ID", studentID).empty())
        {
            Interface::print_note(Csv::multitype("No student with ID:").append(studentID).append(" is found."),
                                  "Student not found");
            Interface::pause();
            return;
        }

        __attendancelist_filter_studentID.assign(studentID);
        edit_attendance_table(attendance_table.filter(__attendancelist_filter_studentID_func));
    }

    void edit_attendance()
    {
        Interface::select_menu select;
        select.set_title("Edit attendance list...");
        select.add_item(1, "In a course");
        select.add_item(2, "Of a student");
        select.add_item(3, "Back");
        while (true)
        {
            int chosen = select.print_menu_and_wait().to_int();
            if (chosen == 1)
                edit_attendance_by_course();
            else
            if (chosen == 2)
                edit_attendance_by_student();
            else
                break;
        }
    }

    void student_check_in (const Csv::multitype& studentID)
    {
        __attendancelist_filter_studentID.assign(studentID);
        Csv::table coursestudent_table = coursestudent.get_table().filter(__attendancelist_filter_studentID_func);
        __courses_filter_valid_courseIDs.destroy();
        for (int i = 0; i < coursestudent_table.num_rows(); ++i)
            __courses_filter_valid_courseIDs.push_back(coursestudent_table.get_row(i).at(0));

        Csv::table &attendance_table = attendancelist.get_table(),
                    courses_table = courses.get_table().filter(__courses_filter_date_func);
        int Nrows = courses_table.num_rows();

        Interface::select_menu select;
        select.set_title(multitype("In-progress lectures (").append(date().now().compile("YYYY/MM/DD hh:mm")).append(")"));
        for (int i = 0; i < Nrows; ++i)
        {
            Csv::list<Csv::multitype> row = courses_table.get_row(i);
            date st, en;
            st.hour = row.at(1).to_int();
            st.minute = row.at(2).to_int();
            en.hour = row.at(3).to_int();
            en.minute = row.at(4).to_int();
            select.add_item(i + 1, Csv::multitype(row.at(0)).append(" (Today ").append(st.compile("hh:mm")).
                                                             append("-").append(en.compile("hh:mm")).append(")"));
        }
        select.add_item(Nrows + 1, "Back");

        int chosen;
        do
        {
            chosen = select.print_menu_and_wait().to_int();
            if (chosen >= 1 && chosen <= Nrows)
            {
                Csv::multitype courseID = courses_table.get_row(chosen - 1).at(0);
                __attendancelist_filter_courseID.assign(courseID);
                if (attendance_table.filter(__attendancelist_filter_studentID_checkin_courseID_func).num_rows() > 0)
                {
                    Interface::print_note("You have checked in this course already during the current session.", "Aborted");
                    Interface::pause();
                }
                else
                {
                    int aNrows = attendance_table.num_rows();
                    date tnow;
                    tnow.now();
                    attendance_table.add_row();
                    attendance_table.get_row(aNrows).at(0) = attendance_table.get_row(aNrows - 1).at(0).to_int() + 1;
                    attendance_table.get_row(aNrows).at(1) = studentID;
                    attendance_table.get_row(aNrows).at(2) = courseID;
                    attendance_table.get_row(aNrows).at(3) = tnow.compile("YYYY/MM/DD hh:mm");
                    attendance_table.get_row(aNrows).at(4) = 1;
                    if (!attendancelist.init_write())
                        break;
                    attendancelist.write_and_terminate();
                    Interface::print_note("Checked in successfully.", "Success");
                    Interface::pause();
                }
            }
        }
        while (chosen != Nrows + 1);
    }

    void view_check_in (const Csv::multitype& studentID)
    {
        __attendancelist_filter_studentID.assign(studentID);
        Interface::print_table(attendancelist.get_table().filter(__attendancelist_filter_studentID_view_mode_func),
                               Csv::multitype("Check-in list of ").append(studentID));
        Interface::pause();
    }
}
