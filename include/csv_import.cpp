#include "csv_import.h"
#include "interface.h"

namespace SMS
{
    csv_handler courselecturer("db/courselecturer.csv");
    csv_handler courses("db/courses.csv");
    csv_handler coursestudent("db/coursestudent.csv");
    csv_handler lecturers("db/lecturers.csv");
    csv_handler scoreboard("db/scoreboard.csv");
    csv_handler semestercourse("db/semestercourse.csv");
    csv_handler semesters("db/semesters.csv");
    csv_handler students("db/students.csv");
    csv_handler users("db/users.csv");
    csv_handler years("db/years.csv");
    csv_handler yearsemester("db/yearsemester.csv");

    void csv_read_util (csv_handler& csv, const multitype& filename)
    {
        if (!csv.init_read())
        {
            Interface::print_note("Importing error!",
                                  Csv::multitype("Database file \"db/").append(filename).append(".csv\" is missing."));
            throw "Data is corrupted.";
            return;
        }
        csv.read_and_terminate();
    }

    void init_all_csvs()
    {
        csv_read_util(courselecturer, "courselecturer");
        csv_read_util(courses, "courses");
        csv_read_util(coursestudent, "coursestudent");
        csv_read_util(lecturers, "lecturers");
        csv_read_util(scoreboard, "scoreboard");
        csv_read_util(semestercourse, "semestercourse");
        csv_read_util(semesters, "semesters");
        csv_read_util(users, "users");
        csv_read_util(years, "years");
        csv_read_util(yearsemester, "yearsemester");
    }
}
