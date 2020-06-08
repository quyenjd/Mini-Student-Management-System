#ifndef CSV_IMPORT_H
#define CSV_IMPORT_H

#include "csv.h"

namespace SMS
{
    using namespace Csv;

    extern csv_handler attendancelist;
    extern csv_handler courselecturer;
    extern csv_handler courses;
    extern csv_handler coursestudent;
    extern csv_handler lecturers;
    extern csv_handler scoreboard;
    extern csv_handler semestercourse;
    extern csv_handler semesters;
    extern csv_handler students;
    extern csv_handler users;
    extern csv_handler years;
    extern csv_handler yearsemester;

    void csv_read_util (csv_handler& csv, const multitype& filename, const list<multitype>& keys);

    // import all csv files.
    void init_all_csvs();
}

#endif // CSV_IMPORT_H
