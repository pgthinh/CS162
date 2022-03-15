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

    string path = "DATA/" + to_string(year) + "/" + to_string(year) + "_" + to_string(term) + "/courses_list/" + to_string(year) + "_" + to_string(term) + "_" + course.CourseID;
    // create a folder (name: year_term_courseID)
    _mkdir(path.c_str());
    ofstream fout;
    
    path += "Course_Data.txt"
    fout.open(path, ofstream::out);

    fout.close();
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