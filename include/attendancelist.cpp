#include "attendancelist.h"
#include "interface.h"
#include "csv_import.h"
#include <ctime>

#define is_leap(Y) (((Y)&3)==0&&((Y)%25!=0||((Y)&15)==0))
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

date::date (const Csv::multitype& _year, const Csv::multitype& _month, const Csv::multitype& _day,
            const Csv::multitype& _hour, const Csv::multitype& _minute)
{
    year = _year.to_int();
    month = Max(1, Min(12, _month.to_int()));
    if (month == 4 || month == 6 || month == 9 || month == 11)
        day = Max(1, Min(30, _day.to_int()));
    else
    if (month == 2)
        day = Max(1, Min(28 + is_leap(year), _day.to_int()));
    else
        day = Max(1, Min(31, _day.to_int()));
    static int _t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int ty = year - month < 3;
    wday = (ty + ty / 4 - ty / 100 + ty / 400 + _t[month - 1] + day) % 7;
    hour = Max(0, Min(23, _hour.to_int()));
    minute = Max(0, Min(59, _minute.to_int()));
}

void date::now()
{
    std::time_t t = std::time(0);
    std::tm *cur = std::localtime(&t);
    year = cur->tm_year + 1900;
    month = cur->tm_mon + 1;
    day = cur->tm_mday;
    wday = cur->tm_wday;
    hour = cur->tm_hour;
    minute = cur->tm_min;
}

date& date::parse (const Csv::multitype& e, const Csv::multitype& format)
{
    year = month = day = 1;
    hour = minute = 0;
    char *_e = e.to_str(),
         *_f = format.to_str();
    int Ne = strlen(_e),
        Nf = strlen(_f);
    if (Ne != Nf)
        return *this;
    bool _year = false,
         _month = false,
         _day = false,
         _hour = false,
         _minute = false;
    for (int i = 0; i < Nf; ++i)
    {
        if (_f[i] == 'Y' && !_year)
        {
            _year = true;
            Csv::multitype __year = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'Y')
                __year = __year.append(_e[++i]);
            year = __year.to_int();
        }
        if (_f[i] == 'M' && !_month)
        {
            _month = true;
            Csv::multitype __month = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'M')
                __month = __month.append(_e[++i]);
            month = __month.to_int();
        }
        if (_f[i] == 'D' && !_day)
        {
            _day = true;
            Csv::multitype __day = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'D')
                __day = __day.append(_e[++i]);
            day = __day.to_int();
        }
        if (_f[i] == 'h' && !_hour)
        {
            _hour = true;
            Csv::multitype __hour = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'h')
                __hour = __hour.append(_e[++i]);
            hour = __hour.to_int();
        }
        if (_f[i] == 'm' && !_minute)
        {
            _minute = true;
            Csv::multitype __minute = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'm')
                __minute = __minute.append(_e[++i]);
            minute = __minute.to_int();
        }
    }
    static int _t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int ty = year - month < 3;
    wday = (ty + ty / 4 - ty / 100 + ty / 400 + _t[month - 1] + day) % 7;
    return *this;
}

Csv::multitype date::compile (const Csv::multitype& format) const
{
    char *s = format.to_str();
    int Ns = strlen(s);
    for (int i = 0; i < Ns / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[Ns - 1 - i];
        s[Ns - 1 - i] = tmp;
    }
    for (int i = 0; i < Ns; ++i)
    {
        if (s[i] == 'Y')
        {
            int _year = year;
            s[i] = char(_year % 10 + '0');
            _year /= 10;
            while (i + 1 < Ns && s[i + 1] == 'Y')
            {
                s[++i] = char(_year % 10 + '0');
                _year /= 10;
            }
        }
        if (s[i] == 'M')
        {
            int _month = month;
            s[i] = char(_month % 10 + '0');
            _month /= 10;
            while (i + 1 < Ns && s[i + 1] == 'M')
            {
                s[++i] = char(_month % 10 + '0');
                _month /= 10;
            }
        }
        if (s[i] == 'D')
        {
            int _day = day;
            s[i] = char(_day % 10 + '0');
            _day /= 10;
            while (i + 1 < Ns && s[i + 1] == 'D')
            {
                s[++i] = char(_day % 10 + '0');
                _day /= 10;
            }
        }
        if (s[i] == 'h')
        {
            int _hour = hour;
            s[i] = char(_hour % 10 + '0');
            _hour /= 10;
            while (i + 1 < Ns && s[i + 1] == 'h')
            {
                s[++i] = char(_hour % 10 + '0');
                _hour /= 10;
            }
        }
        if (s[i] == 'm')
        {
            int _minute = minute;
            s[i] = char(_minute % 10 + '0');
            _minute /= 10;
            while (i + 1 < Ns && s[i + 1] == 'm')
            {
                s[++i] = char(_minute % 10 + '0');
                _minute /= 10;
            }
        }
    }
    for (int i = 0; i < Ns / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[Ns - 1 - i];
        s[Ns - 1 - i] = tmp;
    }
    return Csv::multitype(s);
}

date date::add_day (const Csv::multitype& _day) const
{
    int day = this->day,
        month = this->month,
        year = this->year,
        hour = this->hour,
        minute = this->minute,
        cday = _day.to_int();
    while (cday != 0)
    {
        if (cday < 0)
        {
            --day;
            if (day == 0)
            {
                --month;
                if (month == 0)
                {
                    --year;
                    month = 12;
                }
                day = (month == 4 || month == 6 || month == 9 || month == 11 ? 30 :
                      (month == 2 ? (28 + is_leap(year)) : 31));
            }
            ++cday;
        }
        else
        {
            ++day;
            if (day > (month == 4 || month == 6 || month == 9 || month == 11 ? 30 :
                      (month == 2 ? (28 + is_leap(year)) : 31)))
            {
                ++month;
                if (month > 12)
                {
                    ++year;
                    month = 1;
                }
                day = 1;
            }
            --cday;
        }
    }
    return date(year, month, day, hour, minute);
}

bool date::operator< (const date& d) const
{
    return year != d.year ? (year < d.year) : (month != d.month ? (month < d.month) : (day != d.day ? (day < d.day) : (hour != d.hour ? (hour < d.hour) : (minute < d.minute))));
}

bool date::operator> (const date& d) const
{
    return year != d.year ? (year > d.year) : (month != d.month ? (month > d.month) : (day != d.day ? (day > d.day) : (hour != d.hour ? (hour > d.hour) : (minute > d.minute))));
}

bool date::operator== (const date& d) const
{
    return !(*this < d) && !(*this > d);
}

bool date::operator!= (const date& d) const
{
    return !(*this == d);
}

bool date::operator<= (const date& d) const
{
    return (*this < d) || (*this == d);
}

bool date::operator>= (const date& d) const
{
    return (*this > d) || (*this == d);
}

int date::substract (date d) const
{
    if (*this == d)
        return 0;
    if (*this < d)
        return -d.substract(*this);
    int cnt = 0;
    d.hour = hour;
    d.minute = minute;
    while (*this != d)
    {
        d = d.add_day(1);
        ++cnt;
    }
    return cnt;
}

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
                    break;
                }
                else
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
        select.set_title("Ongoing courses");
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
