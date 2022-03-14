#include "Course.h"

void setCourseRegistration(Time start, Time end) {
    Semester semester = getCurrentSemester();

    string path = "DATA/" + to_string(semester.Year) + '/' + to_string(semester.TheOrderOfSemester) + "/Course_Registration.txt";
    ofstream fout(path);
    fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
    fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
    fout.close();
}
void getCourseRegistration(Time start, Time end) {
    Semester semester = getCurrentSemester();

    string path = "DATA/" + to_string(semester.year) + '/' + to_string(semester.term) + "/Course_Registration.txt";
    ifstream fin(path);
    fin >> start.day >> start.month >> start.year;
    fin >> end.day >> end.month >> end.year;
    fin.close();
}