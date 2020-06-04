#ifndef ATTENDANCELIST_QUYENJD_H
#define ATTENDANCELIST_QUYENJD_H

#include "csv.h"

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
