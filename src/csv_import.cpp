#include "csv_import.h"
#include "interface.h"
#include <exception>

namespace SMS
{
    csv_handler attendancelist("db/attendancelist.csv");
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

    void csv_read_util (csv_handler& csv, const multitype& filename, const list<multitype>& keys)
    {
        if (!csv.init_read())
        {
            Interface::print_note("Importing error!",
                                  Csv::multitype("Database file \"db/").append(filename).append(".csv\" is missing."));
            throw std::runtime_error("Data is corrupted.");
            return;
        }
        csv.read_and_terminate();
        csv.get_table().fix_keys(keys);
    }

    void init_all_csvs()
    {
        csv_read_util(attendancelist, "attendancelist",
                      {"Attendance ID", "Student ID", "Course ID", "Checkin at", "Active"});
        csv_read_util(courselecturer, "courselecturer",
                      {"Course ID", "Username"});
        csv_read_util(courses, "courses",
                      {"Course ID", "Course name", "Class", "Start date", "End date", "Day of week", "Start hour", "Start minute", "End hour", "End minute", "Room"});
        csv_read_util(coursestudent, "coursestudent",
                      {"Course ID", "Student ID"});
        csv_read_util(lecturers, "lecturers",
                      {"Username", "Name", "Degree", "Gender"});
        csv_read_util(scoreboard, "scoreboard",
                      {"Student ID", "Course ID", "Midterm", "Final", "Bonus", "Total"});
        csv_read_util(semestercourse, "semestercourse",
                      {"Semester ID", "Course ID"});
        csv_read_util(semesters, "semesters",
                      {"Semester ID", "Semester name"});
        csv_read_util(students, "students",
                      {"Student ID", "Fullname", "DoB", "Gender", "Class"});
        csv_read_util(users, "users",
                      {"ID", "Pass", "Role"});
        csv_read_util(years, "years",
                      {"Year ID", "Year name"});
        csv_read_util(yearsemester, "yearsemester",
                      {"Year ID", "Semester ID"});
    }
}
