#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{
    void create_academic_year() {   //checked
        Interface::input_menu menu;
        menu.set_title("School Year");
        menu.add_item("School Year");
        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<years.get_table().num_rows();i++) {
            if (years.get_table().get_row(i).at(1).equal(res.at(0))) {
                Interface::print_note ("This school year has already been in the list","Failed");
                Interface::pause();
                return;
            }
        }
        years.get_table().add_row();
        years.get_table().get_row(years.get_table().num_rows()-1).at(0).assign(years.get_table().get_row(years.get_table().num_rows()-2).at(0).to_int()+1);
        years.get_table().get_row(years.get_table().num_rows()-1).at(1).assign(res.at(0));
        Interface::print_note ("Added school year successfully","Success");
        years.init_write();
        years.write_and_terminate();
        Interface::pause();
    }

    void add_new_semester_to_academic_year() {  //checked
        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<years.get_table().num_rows();i++) {
            year_menu.add_item(i+1,years.get_table().get_row(i).at(1));
        }

        year_menu.add_item(years.get_table().num_rows()+1,"Back");
        int select;

        //Choosing a specific year
        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select>=1 && select<=years.get_table().num_rows()) {
                Interface::input_menu menu;
                menu.set_title(multitype("New Semester of ").append(years.get_table().get_row(select-1).at(1)));
                menu.add_item("Semester name");

                list<multitype> res=menu.print_menu_and_wait();

                int check=0;
                for (int j=0;j<semesters.get_table().num_rows();j++) {
                    if (semesters.get_table().get_row(j).at(1).equal(res.at(0))) {
                        Interface::print_note("This semester has already been in this school year","Failed");
                        check=1;
                        Interface::pause();
                    }
                }
                if (check==1) continue;

                //add semester to yearsemester.csv
                yearsemester.get_table().add_row();
                yearsemester.get_table().get_row(yearsemester.get_table().num_rows()-1).at(0).assign(select);
                yearsemester.get_table().get_row(yearsemester.get_table().num_rows()-1).at(1).assign(yearsemester.get_table().get_row(yearsemester.get_table().num_rows()-2).at(1).to_int()+1);

                //add semester to semesters.csv
                semesters.get_table().add_row();
                semesters.get_table().get_row(semesters.get_table().num_rows()-1).at(0).assign(yearsemester.get_table().get_row(yearsemester.get_table().num_rows()-1).at(1));
                semesters.get_table().get_row(semesters.get_table().num_rows()-1).at(1).assign(res.at(0));

                Interface::print_note ("Added semester successfully","Success");

                yearsemester.init_write();
                yearsemester.write_and_terminate();

                semesters.init_write();
                semesters.write_and_terminate();
                Interface::pause();
            }
        } while (select!=years.get_table().num_rows()+1);
    }


    void create_new_course_manually() {
        Interface::input_menu menu;
        menu.set_title("New Course Information");
        menu.add_item("Course ID");
        menu.add_item("Course Name");
        menu.add_item("Class");
        menu.add_item("Start Date (YYYY/MM/DD)");
        menu.add_item("End Date (YYYY/MM/DD)");
        menu.add_item("Day of Week");
        menu.add_item("Start hour");
        menu.add_item("Start Minute");
        menu.add_item("End hour");
        menu.add_item("End Minute");
        menu.add_item("Room");

        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<courses.get_table().num_rows();i++) {
            if (courses.get_table().get_row(i).at(0).equal(res.at(0))) {
                Interface::print_note("This course has already been in the list","Failed");
                Interface::pause();
                return;
            }
        }

        courses.get_table().add_row();
        for (int j=0;j<11;j++) courses.get_table().get_row(courses.get_table().num_rows()-1).at(j).assign(res.at(j));

        Interface::print_note("Added course successfully","Success");

        //Add student to course default
        for (int j=0;j<students.get_table().num_rows();j++) {
            if (students.get_table().get_row(j).at(4).equal(courses.get_table().get_row(courses.get_table().num_rows()-1).at(2))) {
                int checkk=0;
                    for (int k=0;k<coursestudent.get_table().num_rows();k++) {
                        if (students.get_table().get_row(j).at(0).equal(coursestudent.get_table().get_row(k).at(1)) && coursestudent.get_table().get_row(k).at(0).equal(courses.get_table().get_row(courses.get_table().num_rows()-1).at(0))) {
                            checkk=1;
                            break;
                        }
                    }
                if (checkk==0) {
                    coursestudent.get_table().add_row();
                    coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(0).assign(courses.get_table().get_row(courses.get_table().num_rows()-1).at(0));
                    coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(1).assign(students.get_table().get_row(j).at(0));
                }
            }
        }

        Interface::print_note(multitype("Added all student from clase ").append(courses.get_table().get_row(courses.get_table().num_rows()-1).at(2)).append("successfully"),"success");

        coursestudent.init_write();
        coursestudent.write_and_terminate();

        courses.init_write();
        courses.write_and_terminate();
        Interface::pause();
    }

    void update_course_manually() { //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Course list");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(1));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");
        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= courses.get_table().num_rows()) {

                Interface::input_menu menu;

                menu.set_title("Edit Course Information");
                //menu.add_item("Course ID");
                menu.add_item("Course Name");
                menu.add_item("Class");
                menu.add_item("Start Date (YYYY/MM/DD)");
                menu.add_item("End Date (YYYY/MM/DD)");
                menu.add_item("Day of Week");
                menu.add_item("Start hour");
                menu.add_item("Start Minute");
                menu.add_item("End hour");
                menu.add_item("End Minute");
                menu.add_item("Room");

                list<multitype> res=menu.print_menu_and_wait();

                for (int j=0;j<11;j++) courses.get_table().get_row(select-1).at(j+1).assign(res.at(j));

                Interface::print_note("Edited course successful","Success");
                courses.init_write();
                courses.write_and_terminate();
                Interface::pause();
            }
        } while (select != courses.get_table().num_rows()+1);


    }

    void delete_course() {  //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Course List");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(1));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;
        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= courses.get_table().num_rows()) {
                courses.get_table().rm_row(select-1);
                Interface::print_note("Removed course successfully","Success");
                courses.init_write();
                courses.write_and_terminate();
                Interface::pause();
            }
        } while (select != courses.get_table().num_rows()+1);
    }

    void update_academic_year_name() {  //checked
        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<years.get_table().num_rows();i++) {
            year_menu.add_item(i+1,years.get_table().get_row(i).at(1));
        }

        year_menu.add_item(years.get_table().num_rows()+1,"Back");
        int select;

        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <=years.get_table().num_rows()) {
                Interface::input_menu year_update_menu;
                year_update_menu.set_title("Edit School Year's Name");
                year_update_menu.add_item("New name");
                list<multitype> res=year_update_menu.print_menu_and_wait();

                years.get_table().get_row(select-1).at(1).assign(res.at(0));
                Interface::print_note("Edit School Year's Name Successfully","Success");
                years.init_write();
                years.write_and_terminate();
                Interface::pause();
            }
        } while (select != years.get_table().num_rows()+1);

    }

    void update_semester_name() {   //checked
        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semesters.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semesters.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semesters.get_table().num_rows()+1,"Back");
        int select;
        do {
            select=semester_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= semesters.get_table().num_rows()) {

                Interface::input_menu semester_update_menu;
                semester_update_menu.set_title(multitype("Edit Semester ").append(semesters.get_table().get_row(select-1).at(1)));
                semester_update_menu.add_item("New name");

                list<multitype> res=semester_update_menu.print_menu_and_wait();

                semesters.get_table().get_row(select-1).at(1).assign(res.at(0));

                Interface::print_note ("Edit Semester's Name Successfully","Success");
                semesters.init_write();
                semesters.write_and_terminate();
                Interface::pause();
            }
        } while (select != semesters.get_table().num_rows()+1);
    }

    void add_student_to_course() {  //checked
        //show course list
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= courses.get_table().num_rows()) {
                Interface::input_menu student_menu;
                student_menu.set_title("New Student's Information");
                student_menu.add_item("Student ID");

                list<multitype> res=student_menu.print_menu_and_wait();

                int check=0;
                for (int j=0;j<students.get_table().num_rows();j++) {
                    if (students.get_table().get_row(j).at(0).equal(res.at(0))) {
                        check=1;
                        break;
                    }
                }

                if (check==0) {
                    Interface::print_note("There is not any student with this Student ID","Failed");
                    Interface::pause();
                    continue;
                }
                int checkk=0;
                for (int j=0;j<coursestudent.get_table().num_rows();j++) {
                    if (coursestudent.get_table().get_row(j).at(0).equal(courses.get_table().get_row(select-1).at(0)) && coursestudent.get_table().get_row(j).at(1).equal(res.at(0))) {
                        checkk=1;
                        break;
                    }
                }

                if (checkk==1) {
                    Interface::print_note("This student has already been in this course","Failed");
                    Interface::pause();
                    continue;
                }

                //add student to coursestudent.csv
                coursestudent.get_table().add_row();
                coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(0).assign(courses.get_table().get_row(select-1).at(0));
                coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(1).assign(res.at(0));
                Interface::print_note("Added Student To Course Successfully","Success");
                coursestudent.init_write();
                coursestudent.write_and_terminate();
                Interface::pause();
            }
        } while (select != courses.get_table().num_rows()+1);

    }

    void remove_student_from_course() { //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= courses.get_table().num_rows()) {
                Interface::input_menu student_menu;
                student_menu.set_title("Removed Student's Information");
                student_menu.add_item("Student Remove ID");
                list<multitype> res=student_menu.print_menu_and_wait();

                int check=0;

                for (int j=0;j<coursestudent.get_table().num_rows();j++) {
                    if (coursestudent.get_table().get_row(j).at(1).equal(res.at(0)) && coursestudent.get_table().get_row(j).at(0).equal(courses.get_table().get_row(select-1).at(0))) {
                        coursestudent.get_table().rm_row(j);
                        check=1;
                        break;
                    }
                }

                coursestudent.init_write();
                coursestudent.write_and_terminate();

                if (check==0) {
                    Interface::print_note(multitype("No Students With ID:").append(res.at(0)).append(" Found In This Course"), "Failed");
                    Interface::pause();
                }
                else {
                    Interface::print_note(multitype("Removed Student With ID:").append(res.at(0)).append(" From Selected Course"), "Failed");
                    Interface::pause();
                }
            }
        } while (select != courses.get_table().num_rows()+1);
    }

    void add_lecturer_to_course() { //checkeds
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= courses.get_table().num_rows()) {
                Interface::input_menu lecturer_menu;
                lecturer_menu.set_title("Lecturer's Information");
                lecturer_menu.add_item("Lecturer username");

                list<multitype> res=lecturer_menu.print_menu_and_wait();

                int check=0;

                for (int j=0;j<lecturers.get_table().num_rows();j++) {
                    if (lecturers.get_table().get_row(j).at(0).equal(res.at(0))) {
                        check=1;
                        break;
                    }
                }
                if (check==0) {
                    Interface::print_note("No lecturer with this username","Failed");
                    Interface::pause();
                    continue;
                }

                int checkk=0;
                for (int j=0;j<courselecturer.get_table().num_rows();j++) {
                    if (courselecturer.get_table().get_row(j).at(0).equal(courses.get_table().get_row(select-1).at(0)) && courselecturer.get_table().get_row(j).at(1).equal(res.at(0))) {
                        checkk=1;
                        break;
                    }
                }
                if (checkk==1) {
                    Interface::print_note("This lecturer has already been in this course","Failed");
                    Interface::pause();
                    continue;
                }

                //add lecturer to courselecturer.csv
                courselecturer.get_table().add_row();
                courselecturer.get_table().get_row(courselecturer.get_table().num_rows()-1).at(0).assign(courses.get_table().get_row(select-1).at(0));
                courselecturer.get_table().get_row(courselecturer.get_table().num_rows()-1).at(1).assign(res.at(0));
                Interface::print_note("Added lecturer to selected course successfully","Success");

                courselecturer.init_write();
                courselecturer.write_and_terminate();
                Interface::pause();
            }
        } while (select != courses.get_table().num_rows()+1);

    }

    void remove_lecturer_from_course() {    //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= courses.get_table().num_rows()) {
                Interface::input_menu lecturer_menu;
                lecturer_menu.add_item("Lecturer Remove Username");
                list<multitype> res=lecturer_menu.print_menu_and_wait();

                int check=0;
                for (int j=0;j<courselecturer.get_table().num_rows();j++) {
                    if (courselecturer.get_table().get_row(j).at(1).equal(res.at(0)) && courselecturer.get_table().get_row(j).at(0).equal(courses.get_table().get_row(select-1).at(0))) {
                        check=1;
                        courselecturer.get_table().rm_row(j);
                        courselecturer.init_write();
                        courselecturer.write_and_terminate();
                        break;
                    }
                }

                if (check==0) {
                    Interface::print_note(multitype("No Lecturer With Username:").append(res.at(0)).append(" In This Course"),"Failed");
                    Interface::pause();
                }
                else {
                    Interface::print_note(multitype("Removed Lecturer With Username:").append(res.at(0)).append(" Successfully"),"Success");
                    Interface::pause();
                }
            }
        } while (select != courses.get_table().num_rows()+1);
    }

    multitype year_selection;
    bool filter_semester (multitype column, list<multitype>row, table tble) {
        return column.equal("Semester ID") && row.at(tble.get_key("Year ID")).equal(year_selection);
    }

    list<multitype> semester_id_list;
    bool filter_semester_name (multitype column, list<multitype>row,table tble) {
        if (column.equal("Semester name")) {
            for (int i=0;i<semester_id_list.size();i++) {
                if (row.at(tble.get_key("Semester ID")).equal(semester_id_list.at(i))) return true;
            }
        }
        return false;
    }

    void delete_semester_from_academic_year() { //checked
        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<years.get_table().num_rows();i++) {
            year_menu.add_item(i+1,years.get_table().get_row(i).at(1));
        }

        year_menu.add_item(years.get_table().num_rows()+1,"Back");
        int select_year;

        //Choosing a specific year
        do {
            select_year=year_menu.print_menu_and_wait().to_int();
            if (select_year>=1 && select_year<=years.get_table().num_rows()) {

                year_selection=years.get_table().get_row(select_year-1).at(0);
                table new_year_table=yearsemester.get_table().filter(filter_semester);

                semester_id_list.destroy();
                for (int j=0;j<new_year_table.num_rows();j++) {
                    semester_id_list.push_back(new_year_table.get_row(j).at(0));
                }

                table new_semester_table=semesters.get_table().filter(filter_semester_name);

                Interface::select_menu semester_menu;
                semester_menu.set_title("Removed Semester");
                for (int j=0;j<new_semester_table.num_rows();j++) {
                    semester_menu.add_item(j+1,new_semester_table.get_row(j).at(0));
                }

                semester_menu.add_item(new_semester_table.num_rows()+1,"Back");

                int select_semester;
                do {
                    select_semester=semester_menu.print_menu_and_wait().to_int();
                    if (select_semester >=1 && select_semester <= new_semester_table.num_rows()) {
                        yearsemester.get_table().rm_row_where("Semester ID",new_year_table.get_row(select_semester-1).at(0));
                        semesters.get_table().rm_row_where("Semester name",new_semester_table.get_row(select_semester-1).at(0));
                        Interface::print_note("Removed Semester From Year Successfully","Success");
                        Interface::pause();
                        yearsemester.init_write();
                        yearsemester.write_and_terminate();

                        semesters.init_write();
                        semesters.write_and_terminate();
                        break;
                    }
                } while (select_semester != new_semester_table.num_rows()+1);
            }
        } while (select_year!=years.get_table().num_rows()+1);
    }

    multitype CID;
    bool filter_student(multitype column, list<multitype> row, table tble) {
        return column.equal("Student ID") && row.at(tble.get_key("Course ID")).equal(CID);
    }

    list <multitype> student_id_list;
    bool filter_student_course(multitype column, list<multitype> row, table tble) {
        for (int i=0;i<student_id_list.size();i++) {
            if (row.at(tble.get_key("Student ID")).equal(student_id_list.at(i))) return true;
        }
        return false;
    }

    void view_students_of_course() {    //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();

            for (int j=0;j<students.get_table().num_rows();j++) {
                if (students.get_table().get_row(j).at(4).equal(courses.get_table().get_row(select-1).at(2))) {
                    int checkk=0;
                    for (int k=0;k<coursestudent.get_table().num_rows();k++) {
                        if (students.get_table().get_row(j).at(0).equal(coursestudent.get_table().get_row(k).at(1)) && coursestudent.get_table().get_row(k).at(0).equal(courses.get_table().get_row(select-1).at(0))) {
                            checkk=1;
                            break;
                        }
                    }
                    if (checkk==0) {
                        coursestudent.get_table().add_row();
                        coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(0).assign(courses.get_table().get_row(select-1).at(0));
                        coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(1).assign(students.get_table().get_row(j).at(0));
                    }
                }
            }

            if (select >=1 && select <= courses.get_table().num_rows()) {
                CID = courses.get_table().get_row(select-1).at(0);

                table new_student_table=coursestudent.get_table().filter(filter_student);

                student_id_list.destroy();
                for (int j=0;j<new_student_table.num_rows();j++) {
                    student_id_list.push_back(new_student_table.get_row(j).at(0));
                }

                table student_table= students.get_table().filter(filter_student_course);
                Interface::print_table(student_table,multitype("Student List of ").append(courses.get_table().get_row(select-1).at(0)));
                Interface::pause();
                break;
            }
        } while (select != courses.get_table().num_rows()+1);
    }

    multitype Lec_CID;

    bool filter_lecturers (multitype column, list<multitype> row, table tble) {
        return column.equal("Lecturer username") && row.at(tble.get_key("Course ID")).equal(Lec_CID);
    }

    list<multitype> new_lecturers_list;
    bool filter_lecturer_course (multitype column, list<multitype> row, table tble) {
        for (int i=0;i<new_lecturers_list.size();i++) {
            if (row.at(tble.get_key("Username")).equal(new_lecturers_list.at(i))) return true;
        }
        return false;
    }

   /* void view_lecturers_of_course() {   //checked
        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<courses.get_table().num_rows();i++) {
            course_menu.add_item(i+1,courses.get_table().get_row(i).at(0));
        }
        course_menu.add_item(courses.get_table().num_rows()+1,"Back");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= courses.get_table().num_rows()) {
                Lec_CID = courses.get_table().get_row(select-1).at(0);
                table new_lecturer_table=courselecturer.get_table().filter(filter_lecturers);

                new_lecturers_list.destroy();
                for (int j=0;j<new_lecturer_table.num_rows();j++) {
                    new_lecturers_list.push_back(new_lecturer_table.get_row(j).at(0));
                }

                table lecturer_in_course_table= lecturers.get_table().filter(filter_lecturer_course);
                Interface::print_table(lecturer_in_course_table,multitype("Lecturer List of ").append(courses.get_table().get_row(select-1).at(0)));
                Interface::pause();
            }

        } while (select != courses.get_table().num_rows()+1);
    }*/

    void add_course_to_semester() { //checked
        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semesters.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semesters.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semesters.get_table().num_rows()+1,"Back");

        int select_semester;

        do {
            select_semester=semester_menu.print_menu_and_wait().to_int();
            if (select_semester >=1 && select_semester <= semesters.get_table().num_rows()) {
                Interface::select_menu course_menu;
                course_menu.set_title("Which course do you want to add to the semester?");
                for (int j=0;j<courses.get_table().num_rows();j++) {
                    course_menu.add_item(j+1,courses.get_table().get_row(j).at(0));
                }
                course_menu.add_item(courses.get_table().num_rows()+1,"Back");

                int select_course;

                do {
                    select_course = course_menu.print_menu_and_wait().to_int();

                    if (select_course >=1 && select_course <= courses.get_table().num_rows()) {
                        for (int k=0;k<semestercourse.get_table().num_rows();k++) {
                            if (semestercourse.get_table().get_row(k).at(0).equal(semesters.get_table().get_row(select_semester-1).at(0)) && semestercourse.get_table().get_row(k).at(1).equal(courses.get_table().get_row(select_course-1).at(0))) {
                                Interface::print_note("This course has already been in this semester","Failed");
                                Interface::pause();
                                continue;
                            }
                        }

                        semestercourse.get_table().add_row();
                        semestercourse.get_table().get_row(semestercourse.get_table().num_rows()-1).at(0).assign(semesters.get_table().get_row(select_semester-1).at(0));
                        semestercourse.get_table().get_row(semestercourse.get_table().num_rows()-1).at(1).assign(courses.get_table().get_row(select_course-1).at(0));
                        Interface::print_note("Added course to semester successfully","Success");
                        Interface::pause();
                        semestercourse.init_write();
                        semestercourse.write_and_terminate();
                        break;
                    }
                } while (select_course != courses.get_table().num_rows()+1);
            }
        } while (select_semester != semesters.get_table().num_rows()+1);
    }

    multitype semester_id_course;

    bool filter_course_semester(multitype column, list<multitype> row, table tble) {
        return column.equal("Course ID") && row.at(tble.get_key("Semester ID")).equal(semester_id_course);
    }

    void delete_course_from_semester() {    //checked
        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semesters.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semesters.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semesters.get_table().num_rows()+1,"Back");

        int select_semester;

        do {
            select_semester=semester_menu.print_menu_and_wait().to_int();
            if (select_semester >=1 && select_semester <= semesters.get_table().num_rows()) {
                semester_id_course = semesters.get_table().get_row(select_semester-1).at(0);
                table new_semester_course = semestercourse.get_table().filter(filter_course_semester);

                Interface::select_menu course_menu;
                course_menu.set_title("Courses Add");
                for (int j=0;j<new_semester_course.num_rows();j++) {
                    course_menu.add_item(j+1,new_semester_course.get_row(j).at(0));
                }
                course_menu.add_item(new_semester_course.num_rows()+1,"Back");

                int select_course;

                do {
                    select_course = course_menu.print_menu_and_wait().to_int();

                    if (select_course >=1 && select_course <= new_semester_course.num_rows()) {
                        for (int k=0;k<semestercourse.get_table().num_rows();k++) {
                            if (semestercourse.get_table().get_row(k).at(0).equal(semesters.get_table().get_row(select_semester-1).at(0)) && semestercourse.get_table().get_row(k).at(1).equal(new_semester_course.get_row(select_course-1).at(0))) {
                                semestercourse.get_table().rm_row(k);
                                semestercourse.init_write();
                                semestercourse.write_and_terminate();
                                break;
                            }
                        }
                        Interface::print_note("Removed course from semester successfully","Success");
                        Interface::pause();
                        break;
                    }
                } while (select_course != new_semester_course.num_rows()+1);
            }
        } while (select_semester != semesters.get_table().num_rows()+1);
    }

    list<multitype> course_in_semester;
    bool filter_course_print (multitype column, list<multitype> row, table tble) {
        for (int i=0;i<course_in_semester.size();i++) {
            if (row.at(tble.get_key("Course ID")).equal(course_in_semester.at(i))) return true;
        }
        return false;
    }

    void view_course_of_semester() {
        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semesters.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semesters.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semesters.get_table().num_rows()+1,"Back");

        int select_semester;

        do {
            select_semester = semester_menu.print_menu_and_wait().to_int();
            if (select_semester >=1 && select_semester <= semesters.get_table().num_rows()) {
                semester_id_course = semesters.get_table().get_row(select_semester-1).at(0);
                table new_semester_course = semestercourse.get_table().filter(filter_course_semester);

                course_in_semester.destroy();
                for (int f=0;f<new_semester_course.num_rows();f++)
                    course_in_semester.push_back(new_semester_course.get_row(f).at(0));

                table course_semester_table= courses.get_table().filter(filter_course_print);
                Interface::print_table(course_semester_table,multitype("Course list in ").append(semesters.get_table().get_row(select_semester-1).at(1)));
                Interface::pause();
            }
        } while (select_semester != semesters.get_table().num_rows()+1);

    }

    void import_course_from_csv() {
        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semesters.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semesters.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semesters.get_table().num_rows()+1,"Back");

        int select_semester;

        do {
            select_semester = semester_menu.print_menu_and_wait().to_int();
            if (select_semester >=1 && select_semester <= semesters.get_table().num_rows()) {

                Interface::input_menu file_menu;
                file_menu.set_title(multitype("Import course file to ").append(semesters.get_table().get_row(select_semester-1).at(1)));
                file_menu.add_item("File name");
                list<multitype> res=file_menu.print_menu_and_wait();

                csv_handler course_add(res.at(0).to_str());
                if (!course_add.init_read()) {
                    Interface::print_note(multitype("Your file '").append(res.at(0)).append("' is corrupted. Please try again"),"Failed");
                    Interface::pause();
                    continue;
                }
                course_add.read_and_terminate();

                for (int i=0;i<course_add.get_table().num_rows();i++) {
                    int check=0;
                    for (int j=0;j<courses.get_table().num_rows();j++) {
                        if (courses.get_table().get_row(j).at(0).equal(course_add.get_table().get_row(i).at(0))) {
                            check=1;
                            break;
                        }
                    }
                    if (check==0) {
                        courses.get_table().add_row();
                        for (int j=0;j<11;j++) {
                            courses.get_table().get_row(courses.get_table().num_rows()-1).at(j).assign(course_add.get_table().get_row(i).at(j));
                        }
                    }
                }

                courses.init_write();
                courses.write_and_terminate();

                for (int i=0;i<course_add.get_table().num_rows();i++) {
                    int check_c=0;
                    for (int j=0;j<semestercourse.get_table().num_rows();j++) {
                        if (semestercourse.get_table().get_row(j).at(1).equal(course_add.get_table().get_row(i).at(0)) && semestercourse.get_table().get_row(j).at(0).equal(semesters.get_table().get_row(select_semester-1).at(0))) {
                            check_c=1;
                            break;
                        }
                    }
                    if (check_c==0) {
                        semestercourse.get_table().add_row();
                        semestercourse.get_table().get_row(semestercourse.get_table().num_rows()-1).at(0).assign(semesters.get_table().get_row(select_semester-1).at(0));
                        semestercourse.get_table().get_row(semestercourse.get_table().num_rows()-1).at(1).assign(course_add.get_table().get_row(i).at(0));

                        for (int t=0;t<students.get_table().num_rows();t++) {
                            if (students.get_table().get_row(t).at(4).equal(course_add.get_table().get_row(i).at(2))) {
                                int checkk=0;
                                for (int k=0;k<coursestudent.get_table().num_rows();k++) {
                                    if (students.get_table().get_row(t).at(0).equal(coursestudent.get_table().get_row(k).at(1)) && coursestudent.get_table().get_row(k).at(0).equal(course_add.get_table().get_row(i).at(0))) {
                                        checkk=1;
                                        break;
                                    }
                                }
                                if (checkk==0) {
                                    coursestudent.get_table().add_row();
                                    coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(0).assign(course_add.get_table().get_row(i).at(0));
                                    coursestudent.get_table().get_row(coursestudent.get_table().num_rows()-1).at(1).assign(students.get_table().get_row(t).at(0));
                                }
                            }
                        }
                    }
                }
                Interface::print_note("Imported course file successfully","Success");
                coursestudent.init_write();
                coursestudent.write_and_terminate();

                semestercourse.init_write();
                semestercourse.write_and_terminate();
                Interface::pause();
            }
        } while (select_semester != semesters.get_table().num_rows()+1);
    }

    multitype student_id_check;
    bool filter_student_and_course(multitype column, list<multitype> row, table tble) {
        return column.equal("Course ID") && row.at(tble.get_key("Student ID")).equal(student_id_check);
    }

    list<multitype> list_course_id;
    bool filter_schedule (multitype column, list<multitype> row, table tble) {
        for (int i=0;i<list_course_id.size();i++) {
            if (row.at(tble.get_key("Course ID")).equal(list_course_id.at(i))) return true;
        }
        return false;
    }

    void view_schedule_of_student(multitype student_id) {
        student_id_check=student_id;
        table new_student_table=coursestudent.get_table().filter(filter_student_and_course);

        list_course_id.destroy();
        for (int i=0;i<new_student_table.num_rows();i++) {
            list_course_id.push_back(new_student_table.get_row(i).at(0));
        }

        table schedule_table= courses.get_table().filter(filter_schedule);
        Interface::print_table(schedule_table,student_id.append("'s Schedule"));
        Interface::pause();
    }

    bool filter_year(multitype column, list<multitype> row, table tble) {
        return column.equal("Year name");
    }
    void view_all_academic_year() {
        Interface::print_table(years.get_table().filter(filter_year),"School Years");
        Interface::pause();
    }

    void view_semester_in_academic_year() {
        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<years.get_table().num_rows();i++) {
            year_menu.add_item(i+1,years.get_table().get_row(i).at(1));
        }

        year_menu.add_item(years.get_table().num_rows()+1,"Back");
        int select;

        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= years.get_table().num_rows()) {
                year_selection=years.get_table().get_row(select-1).at(0);
                table new_year_table=yearsemester.get_table().filter(filter_semester);
                cout << new_year_table.num_rows();
                semester_id_list.destroy();
                for (int j=0;j<new_year_table.num_rows();j++) {
                    semester_id_list.push_back(new_year_table.get_row(j).at(0));
                }


                table new_semester_table=semesters.get_table().filter(filter_semester_name);

                Interface::print_table(new_semester_table,multitype("Semester of year ").append(years.get_table().get_row(select-1).at(1)));
                Interface::pause();

            }
        } while (select != years.get_table().num_rows()+1);
    }

    void delete_academic_year() {
        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<years.get_table().num_rows();i++) {
            year_menu.add_item(i+1,years.get_table().get_row(i).at(1));
        }

        year_menu.add_item(years.get_table().num_rows()+1,"Back");
        int select;
        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= years.get_table().num_rows()) {
                while (yearsemester.get_table().rm_row_where("Year ID",years.get_table().get_row(select-1).at(0)));
                years.get_table().rm_row(select-1);
                Interface::print_note("Remove school year successfully", "Success");

                yearsemester.init_write();
                yearsemester.write_and_terminate();

                years.init_write();
                years.write_and_terminate();

                Interface::pause();
                break;
            }
        } while (select != years.get_table().num_rows()+1);
    }
};
