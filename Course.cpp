#include "Course.h"
#include "Console.h"

Course getCurrentCourse() {
    string id, name, teacher;
    int nCredits, maxCapacity;
    string day1, ses1, day2, ses2;

    string path = "DATA/cache/currentCourse.txt";
    // string path = "currentCourse.txt";
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
    fout << course->SecondDayOfWeek << ' ' << course->SecondSessionOfWeek;
    fout.close();
}
void updateCurrentCourse() {
    int year, semester;
    string CourseID;
    Course* courseList = NULL;
    cout << "year: "; cin >> year;
    cout << "semester: "; cin >> semester;
    cin.ignore();
    cout << "CourseID: "; getline(cin, CourseID);
    getCourseList(year, semester, courseList);
    Course* courseCur = courseList;
    while (courseCur->next_Course) {
        courseCur = courseCur->next_Course;
    }
    WriteFileCurrentCourse(courseCur);
}
void WriteFileCourseInfoList(int year, int semester, Course* courseList) {
    Course* courseCur = courseList;
    while (courseCur) {
        string pathToInfo = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + courseCur->CourseID + "/info.txt";
        cout << pathToInfo << endl;
        ofstream fileoutToInfo;
        fileoutToInfo.open(pathToInfo, ios::trunc);
        fileoutToInfo << courseCur->CourseID << '\n';
        fileoutToInfo << courseCur->CourseName << '\n';
        fileoutToInfo << courseCur->TeacherName << '\n';
        fileoutToInfo << courseCur->NumberOfCredits << '\n';
        fileoutToInfo << courseCur->MaxNumOfStudent << '\n';
        fileoutToInfo << courseCur->FirstDayOfWeek << ' ';
        fileoutToInfo << courseCur->FirstSessionOfWeek << '\n';
        fileoutToInfo << courseCur->SecondDayOfWeek << ' ';
        fileoutToInfo << courseCur->SecondSessionOfWeek;
        fileoutToInfo.close();
        courseCur = courseCur->next_Course;
    }
}
void getCourseList(int year, int semester, Course*& courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/courseList.txt";
    ifstream fin; fin.open(path, ios::in);
    Course* courseCur = courseList;
    while (!fin.eof()) {
        Course* new_Course = new Course;
        getline(fin, new_Course->CourseID, '\n');
        string pathToInfo = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + new_Course->CourseID + "/info.txt";
        ifstream fileinToInfo;
        fileinToInfo.open(pathToInfo);
        getline(fileinToInfo, new_Course->CourseID, '\n');
        getline(fileinToInfo, new_Course->CourseName, '\n');
        getline(fileinToInfo, new_Course->TeacherName, '\n');
        fileinToInfo >> new_Course->NumberOfCredits; fileinToInfo.ignore();
        fileinToInfo >> new_Course->MaxNumOfStudent; fileinToInfo.ignore();
        getline(fileinToInfo, new_Course->FirstDayOfWeek, ' ');
        getline(fileinToInfo, new_Course->FirstSessionOfWeek, '\n');
        getline(fileinToInfo, new_Course->SecondDayOfWeek, ' ');
        getline(fileinToInfo, new_Course->SecondSessionOfWeek);
        fileinToInfo.close();
        if (!courseCur) { courseCur = new_Course; courseList = new_Course; }
        else {
            courseCur->next_Course = new_Course;
            new_Course->previous_Course = courseCur;
            courseCur = courseCur->next_Course;
        }
    }
    fin.close();
}
void WriteFileCourseList(int year, int semester, Course* courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/courseList.txt";
    ofstream fout;
    fout.open(path, ios::trunc);
    Course* courseCur = courseList;
    while (courseCur) {
        if(courseCur == courseList) fout << courseCur->CourseID;
        else {
            fout << '\n' << courseCur->CourseID;
        }
        courseCur = courseCur->next_Course;
    }
    fout.close();
}
void printCourseInformation(Course* courseCurrent) {
    cout << "\t\t\t\t\t\    ID: " << courseCurrent->CourseID << '\n';
    cout << "\t\t\t\t\t\    Name: " << courseCurrent->CourseName << '\n';
    cout << "\t\t\t\t\t\    Teacher Name: " << courseCurrent->TeacherName << '\n';
    cout << "\t\t\t\t\t\    numCredit: " << courseCurrent->NumberOfCredits << '\n';
    cout << "\t\t\t\t\t\    maxNumStu: " << courseCurrent->MaxNumOfStudent << '\n';
    cout << "\t\t\t\t\t\    D1: S1: " << courseCurrent->FirstDayOfWeek << ' ' << courseCurrent->FirstSessionOfWeek << '\n';
    cout << "\t\t\t\t\t\    D2: S2: " << courseCurrent->SecondDayOfWeek << ' ' << courseCurrent->SecondSessionOfWeek << '\n';
}
void printCourseList(Course* courseList) {
    Course* courseCurrent = courseList;
    while (courseCurrent) {
        printCourseInformation(courseCurrent);
        courseCurrent = courseCurrent->next_Course;
    }
}

// Main Function
// 1. Course registration
void writeFileCourseRegistration(Time start, Time end) {
    Semester semester = getCurrentSemester();
    string path = "DATA/" + to_string(semester.Year) + '/' + to_string(semester.TheOrderOfSemester) + '/' + "registration.txt";

    ofstream fout;
    fout.open(path);
    fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
    fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
    fout.close();
}
void updateCourseRegistration(Time& start, Time& end) {
    clrscr(); Heading();
    gotoxy(0, 15);
    cout << "\n\n\t\t\t\t      ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CREATE COURSE REGISTRATION SESSION "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t    Start date(dd mm yyyy): ";
    cin >> start.day >> start.month >> start.year;
    cout << "\n\n";
    cout << "\t\t\t\t\t    End date(dd mm yyyy)  : ";
    cin >> end.day >> end.month >> end.year;
}
// 2. Add course
void setCourseInformation(Course& course) {
    system("CLS"); Heading();
    cout << "\n\n\t\t\t\t\t\t  ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " ENTER A COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t      Course ID: ";  cin >> course.CourseID;
    cout << "\n\t\t\t\t      Couse name: "; cin.ignore(1); getline(cin, course.CourseName);
    cout << "\n\t\t\t\t      Instructor: "; getline(cin, course.TeacherName);
    cout << "\n\t\t\t\t      Number of credits: "; cin >> course.NumberOfCredits;
    cout << "\n\t\t\t\t      Maximum student: "; cin >> course.MaxNumOfStudent;
    cout << "\n\t\t\t\t      First day of week(MON/TUE/WED/THU/FRI/SAT): "; cin.ignore(1); getline(cin, course.FirstDayOfWeek);
    cout << "\n\t\t\t\t      First session of week(S1/S2/S3/S4): "; getline(cin, course.FirstSessionOfWeek);
    cout << "\n\t\t\t\t      Second day of week(MON/TUE/WED/THU/FRI/SAT): "; getline(cin, course.SecondDayOfWeek);
    cout << "\n\t\t\t\t      Second session of week(S1/S2/S3/S4): "; getline(cin, course.SecondSessionOfWeek);
    cout << "\n\t\t\t\t      Action(commit/back) :"; string confirm; getline(cin, confirm);

    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
    if (confirm == "commit") return;
    else setCourseInformation(course);
}
void addCourse() {
    Course course;
    setCourseInformation(course);

    Semester semester = getCurrentSemester();
    int year = semester.Year;
    int term = semester.TheOrderOfSemester;

    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/course_list/" + course.CourseID;
     _mkdir(path.c_str());

    path += "/info.txt";
    ofstream fout;
    fout.open(path);
    fout << course.CourseID << '\n';
    fout << course.CourseName << '\n';
    fout << course.TeacherName << '\n';
    fout << course.NumberOfCredits << '\n';
    fout << course.MaxNumOfStudent << '\n';
    fout << course.FirstDayOfWeek << ' ' << course.FirstSessionOfWeek << '\n';
    fout << course.SecondDayOfWeek << ' ' << course.SecondSessionOfWeek << '\n';
    fout.close();

    path = "DATA/" + to_string(year) + "/" + to_string(term) + "/course_list/courseList.txt";
    fout.open(path, ios::app);
    fout << "\n" << course.CourseID;
    fout.close();

}
// 3. Update course
void updateCourse(int year, int semester, string CourseID) {
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    cout << '\n';
    Course* courseList = NULL;
    getCourseList(year, semester, courseList);
    Course* courseCur = courseList;
    bool check = false;
    while (courseCur && !check) {
        if (courseCur->CourseID == CourseID) { check = true; break; }
        else courseCur = courseCur->next_Course;
    }
    if (!check) { cout << "\n\t\t\t\t\t\t   The course does not exist" << endl; delay(1500); return; }
    else {
        int select;
        cout << "\t\t\t\t\t   Which feature do you want to update" << endl;
        cout << "\n\t\t\t\t\t   1. Name" << endl;
        cout << "\n\t\t\t\t\t   2. Instructor" << endl;
        cout << "\n\t\t\t\t\t   3. Number of Credit" << endl;
        cout << "\n\t\t\t\t\t   4. Maximum Student" << endl;
        cout << "\n\t\t\t\t\t   5. Day 1" << endl;
        cout << "\n\t\t\t\t\t   6. Session 1" << endl;
        cout << "\n\t\t\t\t\t   7. Day 2" << endl;
        cout << "\n\t\t\t\t\t   8. Session 2" << endl;
        cout << "\n\t\t\t\t\t   Selection: ";
        cin >> select;
        cout << "\n\t\t\t\t\t   Change to: ";
        switch (select) {
        case 1: {cin.ignore(); getline(cin, courseCur->CourseName); }
              break;
        case 2: {cin.ignore(); getline(cin, courseCur->TeacherName); }
              break;
        case 3: cin >> courseCur->NumberOfCredits;
            break;
        case 4: cin >> courseCur->MaxNumOfStudent;
            break;
        case 5: {cin.ignore(); getline(cin, courseCur->FirstDayOfWeek); }
              break;
        case 6: {cin.ignore(); getline(cin, courseCur->FirstSessionOfWeek); }
              break;
        case 7: {cin.ignore(); getline(cin, courseCur->SecondDayOfWeek); }
              break;
        case 8: {cin.ignore(); getline(cin, courseCur->SecondSessionOfWeek); }
              break;
        }
        clrscr(); SetColor(10);
        cout << "\n\t\t\t\t\t\t   The course has been updated successfully:  " << endl;
        SetColor(15);
        printCourseInformation(courseCur); 
        //printCourseList(courseList);
        delay(3000);
        WriteFileCourseInfoList(year, semester, courseList);
        DeleteCourseList(courseList);
        return;
    }
}

// 4. Delete course
void deleteCourse(int year, int semester, string CourseID) {
    Course* courseList = NULL;
    getCourseList(year, semester, courseList);
    Course* courseCur = courseList;
    while (courseCur) {
        if (courseCur->CourseID == CourseID) {
            if (courseCur == courseList) {
                if (courseCur->next_Course == NULL) {
                    DeleteCourseList(courseList); courseList = nullptr;
                }
                else {
                    Course* t = courseList;
                    courseList = courseList->next_Course;
                    courseList->previous_Course = NULL;
                    delete t;
                }
            }
            else if (courseCur->next_Course == NULL) {
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
           /* string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID;
            if (remove(path.c_str()) == 0) cout << "delete successful";
            else " unsuccessful";*/

            SetColor(10);
            cout << "\n\n\t\t\t\t\t       The course has been deleted" << endl;
            SetColor(15);
            delay(1500);
            WriteFileCourseList(year, semester, courseList);
            WriteFileCourseInfoList(year, semester, courseList);
            DeleteCourseList(courseList);
            return;
        }
        else courseCur = courseCur->next_Course;
    }
    SetColor(12);
    cout << "\n\n\t\t\t\t\t       The course does not exist";
    SetColor(15);
    delay(1500);
    DeleteCourseList(courseList);
}
// 5. Course management
void viewCourseMangementMenu() {
    cout << "\n\t\t\t\t\t\t   1. View student" << endl;
    cout << "\n\t\t\t\t\t\t   2. Export scoreboard" << endl;
    cout << "\n\t\t\t\t\t\t   3. Import scoreboard" << endl;
    cout << "\n\t\t\t\t\t\t   4. View scoreboard" << endl;
    cout << "\n\t\t\t\t\t\t   5. Go Back" << endl; // go back to Course Menu;
}

void getCourseMarkList(int year, int semester, string CourseID, Student*& studentList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID + "/marks.txt";
    ifstream fin; fin.open(path, ios::in);
    Student* studentCur = studentList;
    while (!fin.eof()) {
        Student* new_student = new Student;
        getline(fin, new_student->ID, ' ');
        fin >> new_student->mark.totalMark;
        fin >> new_student->mark.finalMark;
        fin >> new_student->mark.midtermMark;
        fin >> new_student->mark.otherMark;
        fin.ignore();
        getline(fin, new_student->Name, '\n');
        if (!studentCur) { studentCur = new_student; studentList = new_student; }
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    fin.close();
}
void getCourseStudentList(int year, int semester, string CourseID, Student*& studentList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID + "/students.txt";
    ifstream fin; fin.open(path, ios::in);
    Student* studentCur = studentList;
    while (!fin.eof()) {
        Student* new_student = new Student;
        getline(fin, new_student->ID, ' ');
        getline(fin, new_student->className, '\n');

        string pathToClass = "CLASS/" + new_student->className + "/" + new_student->ID + ".txt";
        ifstream fileinClass; fileinClass.open(pathToClass, ios::in);

        fileinClass >> new_student->No; fileinClass.ignore();
        getline(fileinClass, new_student->ID, '\n');
        getline(fileinClass, new_student->Name, '\n');
        getline(fileinClass, new_student->Gender, '\n');
        fileinClass >> new_student->Dob.day >> new_student->Dob.month >> new_student->Dob.year;
        fileinClass.ignore();
        getline(fileinClass, new_student->socialID, '\n');
        fileinClass.close();
        if (!studentCur) { studentCur = new_student; studentList = new_student; }
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    fin.close();
}

void viewCourseStudentList(Student* studentList) {
    Student* studentCur = studentList;
    int i = 0;
    while (studentCur) {
        gotoxy(15, 14 + i * 2); cout << i + 1 << ". ";
        gotoxy(20, 14 + i * 2); cout << studentCur->ID;
        gotoxy(35, 14 + i * 2); cout << studentCur->Name;
        gotoxy(65, 14 + i * 2); cout << studentCur->Gender;
        gotoxy(75, 14 + i * 2); cout << studentCur->Dob.day << " " << studentCur->Dob.month << " " << studentCur->Dob.year;
        gotoxy(95, 14 + i * 2); cout << studentCur->socialID << endl;
        i++;
        studentCur = studentCur->next_Student;
    }
    cout << "\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
}
void exportScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student*& studentList) {
    getCourseMarkList(year, semester, CourseID, studentList);
    string path = "csvFile/" + to_string(year) + "/" + to_string(semester) + "/" + CourseID + ".csv";
    ofstream fout; fout.open(path, ios::trunc);
    Student* studentCur = studentList;
    fout << "No,Student ID,Full name,Total mark,Final mark,Midterm mark,Other mark" << '\n';
    int No = 0;
    while (studentCur) {
        if (studentCur->next_Student) {
            fout << ++No << ',' << studentCur->ID << ',' << studentCur->Name << ',' << studentCur->mark.totalMark << ',' << studentCur->mark.finalMark << ',' << studentCur->mark.midtermMark << ',' << studentCur->mark.otherMark << '\n';
        }
        else {
            fout << ++No << ',' << studentCur->ID << ',' << studentCur->Name << ',' << studentCur->mark.totalMark << ',' << studentCur->mark.finalMark << ',' << studentCur->mark.midtermMark << ',' << studentCur->mark.otherMark;
        }
        studentCur = studentCur->next_Student;
    }
    clrscr();
    fout.close();
}
void importScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student* studentList) {
    string path = "csvFile/" + to_string(year) + "/" + to_string(semester) + "/" + CourseID + ".csv";
    ifstream fin; fin.open(path, ios::in);
    Student* studentCur = studentList;
    string temp; getline(fin, temp, '\n');
    while (!fin.eof()) {
        Student* new_student = new Student;
        fin >> new_student->No; fin.ignore(1);
        getline(fin, new_student->ID, ',');
        getline(fin, new_student->Name, ',');
        fin >> new_student->mark.totalMark; fin.ignore(1);
        fin >> new_student->mark.finalMark; fin.ignore(1);
        fin >> new_student->mark.midtermMark; fin.ignore(1);
        fin >> new_student->mark.otherMark; fin.ignore(1);
        if (!studentCur) { studentCur = new_student; studentList = new_student; }
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    /*Student* t = studentCur;
    studentCur->previous_Student->next_Student = nullptr;
    delete t;*/
    fin.close();

    path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID + "/marks.txt";
    ofstream fout; fout.open(path, ios::trunc);
    studentCur = studentList;
    while (studentCur) {
        if (studentCur->next_Student) {
            fout << studentCur->ID << ' ' << studentCur->mark.totalMark << ' ' << studentCur->mark.finalMark << ' ' << studentCur->mark.midtermMark << ' ' << studentCur->mark.otherMark << ' ' << studentCur->Name << '\n';
        }
        else {
            fout << studentCur->ID << ' ' << studentCur->mark.totalMark << ' ' << studentCur->mark.finalMark << ' ' << studentCur->mark.midtermMark << ' ' << studentCur->mark.otherMark << ' ' << studentCur->Name;
        }
        studentCur = studentCur->next_Student;
    }
    fout.close();
    viewScoreboard(studentList);
}
void viewScoreboard(Student* studentList) {
    Student* studentCur = studentList;
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t\t ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    int based = 5; cout.precision(2);
    gotoxy(10 + based, 12); cout << "No";
    gotoxy(15 + based, 12); cout << "Student ID";
    gotoxy(30 + based, 12); cout << "Full name";
    gotoxy(60 + based, 12); cout << "Total";
    gotoxy(70 + based, 12); cout << "Final";
    gotoxy(80 + based, 12); cout << "Midterm";
    gotoxy(90 + based, 12); cout << "Other";
    int i = 0;
    while (studentCur) {
        gotoxy(10 + based, 14 + i * 2); cout << i + 1 << ". ";
        gotoxy(15 + based, 14 + i * 2); cout << studentCur->ID;
        gotoxy(30 + based, 14 + i * 2); cout << studentCur->Name;
        gotoxy(60 + based, 14 + i * 2); cout << studentCur->mark.totalMark;
        gotoxy(70 + based, 14 + i * 2); cout << studentCur->mark.finalMark;
        gotoxy(80 + based, 14 + i * 2); cout << studentCur->mark.midtermMark;
        gotoxy(90 + based, 14 + i * 2); cout << studentCur->mark.otherMark;
        studentCur = studentCur->next_Student;
        i++;
    }
    cout << "\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
    _getch();
}
void manageCourse(int year, int semester, string CourseID) {
    Course* courseList = NULL;
    getCourseList(year, semester, courseList);
    bool check = false;
    Course* courseCur = courseList;
    while (courseCur && !check) {
        if (courseCur->CourseID == CourseID) { check = true; break; }
        else courseCur = courseCur->next_Course;
    }
    if (!check) { SetColor(12); cout << "\n\n\t\t\t\t\t       The course does not exist"; SetColor(15); delay(1500); return; }
    else {
        viewCourseMangementMenu();
        int select;
        cout << "\n\t\t\t\t\t\t   Selection: ";
        cin >> select;
        switch (select)
        {
        case 1: { // view student
            clrscr(); Heading();
            cout << "\n\n\t\t\t\t\t      ";
            for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " STUDENT OF COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
            gotoxy(15, 12); cout << "No";
            gotoxy(20, 12); cout << "Student ID";
            gotoxy(35, 12); cout << "First name";
            gotoxy(65, 12); cout << "Gender";
            gotoxy(75, 12); cout << "Date of birth";
            gotoxy(95, 12); cout << "Social ID";
            Student* CourseStudentList = NULL;
            getCourseStudentList(year, semester, CourseID, CourseStudentList);
            viewCourseStudentList(CourseStudentList);
            DeleteStudentList(CourseStudentList);
            _getch();
        }
              break;
        case 2: { // export scoreboard
            Student* studentList = NULL;
            exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            DeleteStudentList(studentList);
            SetColor(10);
            cout << "\n\n\t\t\t\t\t\t   Export successfully!";
            SetColor(15);
            delay(2000);
        }
              break;
        case 3: { // import scoreboard
            Student* studentList = NULL;
            //exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            importScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            DeleteStudentList(studentList);
        }
              break;
        case 4: { // view scoreboard
            Student* studentList = NULL;
            exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            viewScoreboard(studentList);
            DeleteStudentList(studentList);
        }
              break;
        case 5:
            courseMenu();
            break;
        }
    }
    DeleteCourseList(courseList);
}

void courseMenu() {
    clrscr(); Heading();
    gotoxy(0, 10);
    cout << "\n\n\t\t\t\t\t\t";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " COURSE MENU "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t     1. Create course registration\n\n";
    cout << "\t\t\t\t\t     2. Add a course\n\n";
    cout << "\t\t\t\t\t     3. Update a course\n\n";
    cout << "\t\t\t\t\t     4. Delete a course\n\n";
    cout << "\t\t\t\t\t     5. Choose a course to manage\n\n";
    cout << "\t\t\t\t\t     6. Go back\n\n";
    int select;
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
    cout << "\n\t\t\t\t\t     Select number: "; cin >> select;
    switch (select)
    {
    case 1: {
        Time startDate, endDate;
        updateCourseRegistration(startDate, endDate);
        writeFileCourseRegistration(startDate, endDate);
        courseMenu();
    }
          break;
    case 2: {
        addCourse();
        courseMenu();
    }
          break;
    case 3: {
        int year;
        int semester;
        string CourseID;
        clrscr(); Heading();
        cout << "\n\n\t\t\t\t\t       ";
        for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " UPDATE A COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
        cout << "\n\n";
        cout << "\t\t\t\t\t\t      Year: "; cin >> year;
        cout << "\n\t\t\t\t\t\t      Semester: "; cin >> semester;
        cout << "\n\t\t\t\t\t\t      Course ID: "; cin.ignore(1); getline(cin, CourseID, '\n');
        updateCourse(year, semester, CourseID);
        courseMenu();
    }
          break;
    case 4: {
        int year;
        int semester;
        string CourseID;
        clrscr(); Heading();
        cout << "\n\n\t\t\t\t\t       ";
        for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " REMOVE A COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
        cout << "\n\n";
        cout << "\n\t\t\t\t\t\t    Year: "; cin >> year;
        cout << "\n\t\t\t\t\t\t    Semester: "; cin >> semester;
        cout << "\n\t\t\t\t\t\t    Course ID: "; cin.ignore(1); getline(cin, CourseID, '\n');
        deleteCourse(year, semester, CourseID);
        courseMenu();
    }
          break;
    case 5: {
        int year;
        int semester;
        string CourseID;
        clrscr(); Heading();
        cout << "\n\n\t\t\t\t\t       ";
        for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " MANAGE COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
        cout << "\n\n\t\t\t\t\t\t    Year: "; cin >> year;
        cout << "\n\t\t\t\t\t\t    Semester: "; cin >> semester;
        cout << "\n\t\t\t\t\t\t    Course ID: "; cin.ignore(1); getline(cin, CourseID, '\n');
        manageCourse(year, semester, CourseID);
        courseMenu();
    }
          break;
    case 6: {
        return;
    }
          break;
    }
}

