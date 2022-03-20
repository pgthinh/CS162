#include "Course.h"

Semester getCurrentSemester() {
    int year;
    int term;
    int startday, startmonth, startyear;
    int endday, endmonth, endyear;
    
    string path = "DATA/cache/currentSemester.txt";
    ifstream fin(path);
    fin >> year;
    fin >> term;
    fin >> startday >> startmonth >> startyear;
    fin >> endday >> endmonth >> endyear;
    fin.close();

    return Semester(year, term, Time(startday, startmonth, startyear), Time(endday, endmonth, endyear));
}
Course getCurrentCourse() {
    string id, name, teacher;
    int nCredits, maxCapacity;
    string day1, ses1, day2, ses2;

   string path = "DATA/cache/currentCourse.txt";
    // string path = "/Users/apple/Documents/Tài Liiệu đại học/Năm 1/HK2/CS162/Project/updateCourse/currentCourse.txt";
    ifstream fin(path);
    getline(fin, id);
    getline(fin, name);
    getline(fin, teacher);
    fin >> nCredits;
    fin >> maxCapacity;
    fin >> day1 >> ses1;
    fin >> day2 >> ses2;
    fin.close();

    return Course(id, name, teacher, nCredits, maxCapacity, day1, ses1, day2, ses2);
}
// Common Function
void WriteFileCurrentCourse(Course* course) {
    string path = "DATA/cache/currentCourse.txt";
    ofstream fout;
    fout.open(path, ios::app);
    fout << course->CourseID << '\n';
    fout << course->CourseName << '\n';
    fout << course->TeacherName << '\n';
    fout << course->NumberOfCredits << '\n';
    fout << course->MaxNumOfStudent << '\n';
    fout << course->FirstDayOfWeek << ' ' << course->FirstSessionOfWeek << '\n';
    fout << course->SecondDayOfWeek << ' ' << course->SecondSessionOfWeek << '\n';
    fout.close();
}
void WriteFileCourseList(int year, int semester, Course* courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(year) + "_" + to_string(semester) + "/course_list/Course_List.txt";    
    ofstream fout;
    fout.open(path, ios::trunc);
    Course* courseCur = courseList;
    while(courseCur) {
        fout << courseCur->CourseID << '\n';
        fout << courseCur->CourseName << '\n';
        fout << courseCur->TeacherName << '\n';
        fout << courseCur->NumberOfCredits << '\n';
        fout << courseCur->MaxNumOfStudent << '\n';
        fout << courseCur->FirstDayOfWeek << ' ' << courseCur->FirstSessionOfWeek << '\n';
        if(!courseCur->next_Course) fout << courseCur->SecondDayOfWeek << ' ' << courseCur->SecondSessionOfWeek;
        else fout << courseCur->SecondDayOfWeek << ' ' << courseCur->SecondSessionOfWeek << '\n';
        courseCur = courseCur->next_Course;
    }
    fout.close();
}
void printCourseInformation(Course* courseCurrent) {
    cout << "ID: " << courseCurrent->CourseID << '\n';
    cout << "Name: " << courseCurrent->CourseName << '\n';
    cout << "Teacher Name: " << courseCurrent->TeacherName << '\n';
    cout << "numCredit: " << courseCurrent->NumberOfCredits << '\n';
    cout << "maxNumStu: " << courseCurrent->MaxNumOfStudent << '\n';
    cout << "D1: S1: " << courseCurrent->FirstDayOfWeek << ' ' << courseCurrent->FirstSessionOfWeek << '\n';
    cout << "D2: S2: " << courseCurrent->SecondDayOfWeek << ' ' << courseCurrent->SecondSessionOfWeek << '\n';
}
void printCourseList(Course* courseList) {
    Course* courseCurrent = courseList;
    while(courseCurrent) {
        printCourseInformation(courseCurrent);
        courseCurrent = courseCurrent->next_Course;
    }
}
void deleteCourseList(Course* &courseList) {
    while(courseList) {
        Course* t = courseList;
        courseList = courseList->next_Course;
        delete t;
    }
}
// Main Function
void setCourseRegistration(Time start, Time end) {
    Semester semester = getCurrentSemester();
    string path = "DATA/" + to_string(semester.Year) + '/' + to_string(semester.TheOrderOfSemester) + "/Course_Registration.txt";
    ofstream fout(path);
    fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
    fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
    fout.close();
}
void getCourseRegistration(Time &start, Time &end) {
    Semester semester = getCurrentSemester();

    string path = "DATA/" + to_string(semester.Year) + '/' + to_string(semester.TheOrderOfSemester) + "/Course_Registration.txt";
    ifstream fin(path);
    fin >> start.day >> start.month >> start.year;
    fin >> end.day >> end.month >> end.year;
    fin.close();
}
void setCourseInformation(Course &course) {
    cout << "SET COURSE INFORMATION";
    cout << endl << "Course ID: "; cin >> course.CourseID;
    cout << endl << "Course Name: "; getline(cin, course.CourseName);
    cout << endl << "Teacher Name: "; getline(cin, course.TeacherName);
    cout << endl << "Number of Credits: "; cin >> course.NumberOfCredits;
    cout << endl << "Maximum Students: "; cin >> course.MaxNumOfStudent;
    cout << endl << "Day 1: "; getline(cin, course.FirstDayOfWeek);
    cout << endl << "Session: "; getline(cin, course.FirstSessionOfWeek);
    cout << endl << "Day 2: "; getline(cin, course.SecondDayOfWeek);
    cout << endl << "Session: "; getline(cin, course.SecondSessionOfWeek);
}
void addCourse() {
    Course course;
    setCourseInformation(course);
    
    Semester semester = getCurrentSemester();
    int year = semester.Year;
    int term = semester.TheOrderOfSemester;

    string path = "DATA/" + to_string(year) + "/" + to_string(year) + "_" + to_string(term) + "/courses_list/" + course.CourseID;
    // create a folder (name: year_term_courseID)
    _mkdir(path.c_str());
    ofstream fout;
    // create a data file for a course
    path += "Course_Data.txt";
    fout.open(path, ofstream::out);
    fout.close();
    // add course's informations to the CourseList
    path = "DATA/" + to_string(year) + "/" + to_string(year) + "_" + to_string(term) + "/courses_list/" + "Course_List.txt";
    fout.open(path, ofstream::out | ofstream::app);
    fout << course.CourseID << '\n';
    fout << course.CourseName << '\n';
    fout << course.TeacherName << '\n';
    fout << course.NumberOfCredits << '\n';
    fout << course.MaxNumOfStudent << '\n';
    fout << course.FirstDayOfWeek << ' ' << course.FirstSessionOfWeek << '\n';
    fout << course.SecondDayOfWeek << ' ' << course.SecondSessionOfWeek << '\n';
    fout.close();
}
void getCourseList(int year, int semester, Course* &courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(year) + "_" + to_string(semester) + "/course_list/Course_List.txt";
    fstream fin; fin.open("path");
    Course* courseCur = courseList;
    while(!fin.eof()) {
        Course* new_Course = new Course;
        getline(fin, new_Course->CourseID);
        getline(fin, new_Course->CourseName);
        getline(fin, new_Course->TeacherName);
        fin >> new_Course->NumberOfCredits;
        fin >> new_Course->MaxNumOfStudent;
        fin >> new_Course->FirstDayOfWeek >> new_Course->FirstSessionOfWeek;
        fin >> new_Course->SecondDayOfWeek >> new_Course->SecondSessionOfWeek;
        fin.ignore(1);
        if(!courseCur) {courseCur = new_Course; courseList = new_Course;}
        else {
            courseCur->next_Course = new_Course;
            new_Course->previous_Course = courseCur;
            courseCur = courseCur->next_Course;
        }
    }
    fin.close();
}
void updateCourse() {
    int year, semester;
    string CourseID;
    Course* courseList = NULL;
    cout<< "year: "; cin >> year;
    cout << "semester: " ; cin >> semester;
    cin.ignore();
    cout << "CourseID: "; getline(cin, CourseID);
    getCourseList(year, semester, courseList);
    Course* courseCur = courseList;
    bool check = false;
    while(courseCur && !check) {
        if(courseCur->CourseID == CourseID) { check = true; break;}
        else courseCur = courseCur->next_Course;
    }
    if(!check){ cout << "The course does not exist"; return;}
    else {
        int select;
        cout << "Which feature do you want to update";cout << "1. ID" << endl;cout << "2. Name" << endl;cout << "3. Teacher Name" << endl;cout << "4. NumCredit" << endl;cout << "5. MaxNumStu" << endl;cout << "6. D1" << endl;cout << "7. S1" << endl;cout << "8. D2" << endl;cout << "9. S2" << endl;
        cin >> select;
        cout << "Change to: ";
        switch (select) {
            case 1: {cin.ignore();getline(cin,courseCur->CourseID);}
                break;
            case 2: {cin.ignore();getline(cin,courseCur->CourseName);}
                break;
            case 3: {cin.ignore();getline(cin,courseCur->TeacherName);}
                break;
            case 4: cin >> courseCur->NumberOfCredits;
                break;
            case 5: cin >> courseCur->MaxNumOfStudent;
                break;
            case 6: cin >> courseCur->FirstDayOfWeek;
                break;
            case 7: cin >> courseCur->FirstSessionOfWeek;
                break;
            case 8: cin >> courseCur->SecondDayOfWeek;
                break;
            case 9: cin >> courseCur->SecondSessionOfWeek;
                break;
        }
        cout << "The course has been updated: " << endl;
        printCourseInformation(courseCur);
        WriteFileCourseList(year, semester, courseList);
        deleteCourseList(courseList);
    }
}
void deleteCourse() {
    int year, semester;
    string CourseID;
    Course* courseList = NULL;
    cout<< "year: "; cin >> year;
    cout << "semester: " ; cin >> semester;
    getCourseList(year, semester, courseList);
    printCourseList(courseList);
    cin.ignore();
    cout << "CourseID that you want to delete: "; getline(cin, CourseID);
    Course* courseCur = courseList;
    while(courseCur) {
        if(courseCur->CourseID == CourseID) {
            if(courseCur == courseList) {
                if(courseCur->next_Course == NULL) deleteCourseList(courseList);
                else {
                    Course* t = courseList;
                    courseList = courseList->next_Course;
                    courseList->previous_Course = NULL;
                    delete t;
                }
            }
            else if(courseCur->next_Course == NULL) {
                Course* t = courseCur;
                courseCur->previous_Course->next_Course = NULL;
                delete t;
            }
            else {
                Course* t = courseCur;
                courseCur->previous_Course->next_Course = courseCur->next_Course;
                courseCur->next_Course->previous_Course = courseCur->previous_Course;
                courseCur->next_Course = NULL;
                courseCur->previous_Course = NULL;
                delete t;
            }
            cout << "The course has been deleted" << endl;
            WriteFileCourseList(year, semester, courseList);
            deleteCourseList(courseList);
            return;
        }
        else courseCur = courseCur->next_Course;
    }
    cout << "The course does not exist";
    deleteCourseList(courseList);
}



