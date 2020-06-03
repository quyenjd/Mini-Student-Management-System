#ifndef ATTENDANCELIST_QUYENJD_H
#define ATTENDANCELIST_QUYENJD_H

#include "csv.h"

struct date
{
    int year, month, day, wday /* 0 = Sunday, 1 = Monday, etc. */, hour, minute;

    // constructor.
    date (const Csv::multitype& _year = 1,
          const Csv::multitype& _month = 1,
          const Csv::multitype& _day = 1,
          const Csv::multitype& _hour = 0,
          const Csv::multitype& _minute = 0);

    // set date to current time.
    void now();

    // parse string into time.
    // syntax: 'Y' for year, 'M' for month, 'D' for day, 'h' for hour, 'm' for minute.
    date& parse (const Csv::multitype& e, const Csv::multitype& format);

    // compile date to string.
    // syntax: 'Y' for year, 'M' for month, 'D' for day, 'h' for hour, 'm' for minute.
    Csv::multitype compile (const Csv::multitype& format) const;

    // add days.
    date add_day (const Csv::multitype& _day) const;

    // compare operators.
    bool operator<  (const date& d) const;
    bool operator>  (const date& d) const;
    bool operator== (const date& d) const;
    bool operator!= (const date& d) const;
    bool operator<= (const date& d) const;
    bool operator>= (const date& d) const;

    // calculate (*this) - d and give the result in day unit.
    // hour and minute are not involved.
    int substract (date d) const;
};

namespace SMS
{
    void view_attendance_list();
    void export_attendance_list_to_csv();
    void edit_attendance_table (const Csv::table& tabl);
    void edit_attendance_by_course();
    void edit_attendance_by_student();
    void edit_attendance();
    void student_check_in (const Csv::multitype& studentID);
    void view_check_in (const Csv::multitype& studentID);
}

#endif // ATTENDANCELIST_QUYENJD_H
