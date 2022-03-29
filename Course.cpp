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
    fout << course->SecondDayOfWeek << ' ' << course->SecondSessionOfWeek << '\n';
    fout.close();
}
void updateCurrentCourse() {
    int year, semester;
    string CourseID;
    Course* courseList = NULL;
    cout<< "year: "; cin >> year;
    cout << "semester: " ; cin >> semester;
    cin.ignore();
    cout << "CourseID: "; getline(cin, CourseID);
    getCourseList(year, semester, courseList);
    Course* courseCur = courseList;
    while(courseCur->next_Course) {
        courseCur = courseCur->next_Course;
    }
    WriteFileCurrentCourse(courseCur);
}
void getCourseInfoList(int year, int semester, Course* &courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/courseList.txt";
    fstream fin; fin.open(path, ios::in);
    Course* courseCur = courseList;
    while(!fin.eof()) {
        Course* new_Course = new Course;
        getline(fin, new_Course->CourseID, '\n');
        string pathToInfo = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + new_Course->CourseID + "/info.txt";
        fstream fileinToInfo; fileinToInfo.open(path);
        getline(fin, new_Course->CourseID, ',');
        getline(fin, new_Course->CourseName, ',');
        getline(fin, new_Course->TeacherName, ',');
        fin >> new_Course->NumberOfCredits; fin.ignore();
        fin >> new_Course->MaxNumOfStudent;fin.ignore();
        getline(fin, new_Course->FirstDayOfWeek, ',');
        getline(fin, new_Course->FirstSessionOfWeek, ',');
        getline(fin, new_Course->SecondDayOfWeek, ',');
        getline(fin, new_Course->SecondSessionOfWeek);
        fileinToInfo.close();
        if(!courseCur) {courseCur = new_Course; courseList = new_Course;}
        else {
            courseCur->next_Course = new_Course;
            new_Course->previous_Course = courseCur;
            courseCur = courseCur->next_Course;
        }
    }
    fin.close();
}
void WriteFileCourseInfoList(int year, int semester, Course* courseList) {
    Course* courseCur = courseList;
    while(courseCur) {
        string pathToInfo = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + courseCur->CourseID + "/info.txt";
        fstream fileoutToInfo; fileoutToInfo.open(path, ios::trunc);
        fout << courseCur->CourseID << '\n';
        fout << courseCur->CourseName << '\n';
        fout << courseCur->TeacherName << '\n';
        fout << courseCur->NumberOfCredits << '\n';
        fout << courseCur->MaxNumOfStudent << '\n';
        fout << courseCur->FirstDayOfWeek << '\n';
        fout << courseCur->FirstSessionOfWeek << '\n';
        fout << courseCur->SecondDayOfWeek << '\n';
        fout << courseCur->SecondSessionOfWeek;
        fileoutToInfo.close();
        courseCur = courseCur->next_Course;
        }
    fin.close();
}
void getCourseList(int year, int semester, Course* &courseList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/courseList.txt";
    fstream fin; fin.open(path, ios::in);
    Course* courseCur = courseList;
    while(!fin.eof()) {
        Course* new_Course = new Course;
        getline(fin, new_Course->CourseID, ',');
        if(!courseCur) {courseCur = new_Course; courseList = new_Course;}
        else {
            courseCur->next_Course = new_Course;
            new_Course->previous_Course = courseCur;
            courseCur = courseCur->next_Course;
        }
    }
    fin.close();
}
void WriteFileCourseList(int year, int semester, Course* courseList) {
    string path = "DATA/" + to_string(year)+ "/" + to_string(semester) + "/course_list/courseList.txt";
    ofstream fout;
    fout.open(path, ios::trunc);
    Course* courseCur = courseList;
    while(courseCur) {
        fout << courseCur->CourseID << ',';
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
void updateCourseRegistration(Time &start, Time &end) {
    cout << "Start day month year: ";
    cin >> start.day >> start.month >> start.year;
    cout << "End day month year: ";
    cin >> end.day >> end.month >> end.year;
}
// 2. Add course
void setCourseInformation(Course &course) {
    cout << "SET COURSE INFORMATION" << endl;
    cout << "Course ID: "; cin >> course.CourseID;
    cout << "Course Name: "; cin.ignore(1); getline(cin, course.CourseName);
    cout << "Teacher Name: "; getline(cin, course.TeacherName);
    cout << "Number of Credits: "; cin >> course.NumberOfCredits;
    cout << "Maximum Students: "; cin >> course.MaxNumOfStudent;
    cout << "Day 1: "; cin.ignore(1); getline(cin, course.FirstDayOfWeek);
    cout << "Session: "; getline(cin, course.FirstSessionOfWeek);
    cout << "Day 2: "; getline(cin, course.SecondDayOfWeek);
    cout << "Session: "; getline(cin, course.SecondSessionOfWeek);
}
void addCourse() {
    Course course;
    setCourseInformation(course);
    
    Semester semester = getCurrentSemester();
    int year = semester.Year;
    int term = semester.TheOrderOfSemester;

    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/courses_list/" + course.CourseID;
    mkdir(path);

    path += "info.txt";
    fout.open(path, ofstream::out | ofstream::app);
    fout << course.CourseID << '\n';
    fout << course.CourseName << '\n';
    fout << course.TeacherName << '\n';
    fout << course.NumberOfCredits << '\n';
    fout << course.MaxNumOfStudent << '\n';
    fout << course.FirstDayOfWeek << ' ' << course.FirstSessionOfWeek << '\n';
    fout << course.SecondDayOfWeek << ' ' << course.SecondSessionOfWeek << '\n';
    fout.close();  

    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/courses_list/courseList.txt";
    ofstream fout; fout.open(path);
    fout << course.CourseID << '\n';
    fout.close();
    
}
// 3. Update course
void updateCourse(int year, int semester, string CourseID) {
    Course* courseList = NULL;
    getCourseInfoList(year, semester, courseList);
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
        WriteFileCourseInfoList(year, semester, courseList);

        deleteCourseList(courseList);
        return;
    }
    deleteCourseList(courseList);
}
// 4. Delete course
void deleteCourse(int year, int semester, string CourseID) {
    Course* courseList = NULL;
    getCourseInfoList(year,semester,courseList);
    Course* courseCur = courseList;
    while(courseCur) {
        if(courseCur->CourseID == CourseID) {
            if(courseCur == courseList) {
                if(courseCur->next_Course == NULL) {
                    deleteCourseList(courseList);
                }
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
            WriteFileCourseInfoList(year, semester, courseList);
            deleteCourseList(courseList);
            return;
        }
        else courseCur = courseCur->next_Course;
    }
    cout << "The course does not exist";
    deleteCourseList(courseList);
}
// 5. Course management
void viewCourseMangementMenu() {
    cout << "1. View student" << endl;
    cout << "2. Export scorebroad" << endl;
    cout << "3. Import scorebroad" << endl;
    cout << "4. View scorebroad" << endl;
    cout << "5. Go Back" << endl; // go back to Course Menu;
}

void getCourseMarkList(int year, int semester, string CourseID, Student* &studentList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID + "/marks.txt";
    fstream fin; fin.open(path);
    Student* studentCur = studentList;
    while(!fin.eof()) {
        Student* new_student = new Student;
        getline(fin, new_student->ID, ' ');
        fin >> new_student->mark.totalMark; 
        fin >> new_student->mark.finalMark;
        fin >> new_student->mark.midtermMark;
        fin >> new_student->mark.otherMark;
        fin.ignore();
        getline(fin, new_student->Name, '\n');
        if(!studentCur) {studentCur = new_student; studentList = new_student;}
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    fin.close();
}
void getCourseStudentList(int year, int semester, string CourseID, Student* &studentList) {
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + CourseID + "/students.txt";
    fstream fin; fin.open(path);
    Student* studentCur = studentList;
    while(!fin.eof()) {
        Student* new_student = new Student;
        getline(fin, new_student->ID, ' ');
        getline(fin,new_student->className, '\n');
        string pathToClass = "CLASS/" + new_student->className + "/" + new_student->ID + ".txt";
        fstream fileinClass; fileinClass.open(pathToClass, ios::in);
        fin >> new_student->No; fin.ignore();
        getline(fin, new_student->ID, '\n');
        getline(fin, new_student->Name, '\n');
        getline(fin, new_student->Gender, '\n');
        fin >> new_student->Dob.day; fin >> new_student->Dob.month; fin >> new_student->Dob.year; fin.ignore();
        getline(fin, new_student->socialID, '\n');
        fileinClass.close();
        if(!studentCur) {studentCur = new_student; studentList = new_student;}
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    fin.close();
}
void viewCourseStudent(Student* student) {
    cout << student->ID << endl;
    cout << student->Name << endl;
    cout << student->Gender << endl;
    cout << student->Dob.day << " " << student->Dob.month << " " << student->Dob.year << endl;
    cout << student->socialID << endl;
}
void viewCourseStudentList(Student* studentList) {
    Student* studentCur = studentList;
    while(studentCur) {
        viewCourseStudent(studentCur);
        studentCur = studentCur->next_Student;
    }
}
void exportScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student* &studentList) {
    getCourseMarkList(year, semester, CourseID, studentList);
    string path = "csvFile/" + to_string(year) + "/" + to_string(semester) + CourseID + ".csv";
    fstream fout; fout.open(path);
    Student* studentCur = studentList;
    while(studentCur) {
        fout << studentCur->No << ',' << studentCur->Name << ',' << studentCur->mark.totalMark << ',' << studentCur->mark.finalMark << ',' << studentCur->mark.midtermMark << ',' << studentCur->mark.otherMark << '\n';
        studentCur = studentCur->next_Student;
    }
    fout.close();
}
void importScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student* studentList) {
    string path = "csvFile/" + to_string(year) + "/" + to_string(semester) + CourseID + ".csv";
    fstream fin; fin.open(path);
    Student* studentCur = studentList;
    while(!fin.eof()) {
        Student* new_student = new Student;
        fin >> new_student->No; fin.ignore(1);
        getline(fin, new_student->ID, ',');
        getline(fin, new_student->Name, ',');
        fin >> new_student->mark.totalMark; fin.ignore(1);
        fin >> new_student->mark.finalMark; fin.ignore(1);
        fin >> new_student->mark.midtermMark; fin.ignore(1);
        fin >> new_student->mark.otherMark;
        fin.ignore();
        if(!studentCur) {studentCur = new_student; studentList = new_student;}
        else {
            studentCur->next_Student = new_student;
            new_student->previous_Student = studentCur;
            studentCur = studentCur->next_Student;
        }
    }
    fin.close();
    viewScoreboard(studentList);
}
void viewScoreboard(Student* studentList) {
    Student* studentCur = studentList;
    while(studentCur) {
        cout << studentCur->No << ' ' << studentCur->Name << ' ' << studentCur->mark.totalMark << ' ' << studentCur->mark.finalMark << ' ' << studentCur->mark.midtermMark << ' ' << studentCur->mark.otherMark << '\n';
        studentCur = studentCur->next_Student;
    }
}
void manageCourse(int year, int semester) {
    Course* courseList = NULL;
    getCourseInfoList(year, semester, courseList);
    string CourseID;
    cout << "Choose CourseID to manage" << endl;
    printCourseList(courseList);
    cout << "CourseID: "; getline(cin, CourseID);
    bool check = false;
    Course* courseCur = courseList;
    while(courseCur && !check) {
        if(courseCur->CourseID == CourseID) { check = true; break;}
        else courseCur = courseCur->next_Course;
    }
    if(!check){ cout << "The course does not exist"; return;}
    else {
        viewCourseMangementMenu();
        int select;
        cout << "Select the number: ";
        cin >> select;
        switch (select)
        {
            case 1: { // view student
                Student* CourseStudentList;
                getCourseStudentList(year, semester, CourseID, CourseStudentList);
                viewCourseStudentList(CourseStudentList);
            }
                break;
            case 2: { // export scoreboard
                Student* studentList;
                exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            }
                break;
            case 3: { // import scoreboard
                Student* studentList;
                exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
                importScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
            }
                break;
            case 4: { // view scoreboard
                Student* studentList;
                exportScoreboardOfStudentListOfCourse(year, semester, CourseID, studentList);
                viewScoreboard(studentList);
            }
                break;
            case 5:
                courseMenu();
                break;
        }
    }
}

void courseMenu() {
    cout << "1. Create course registration" << endl;
    cout << "2. Add course" << endl;
    cout << "3. Update course" << endl;
    cout << "4. Delete course" << endl;
    cout << "5. Choose course to manage" << endl;
    cout << "6. Go back" << endl;
    int select;
    cout << "Select number: "; cin >> select;
    switch(select)
    {
    case 1:  {
        Time startDate, endDate;
        updateCourseRegistration(startDate, endDate);
        writeFileCourseRegistration(startDate, endDate);
    }
            break;
    case 2: {
        addCourse();
    }
            break;
    case 3: {
        int year;
        int semester;
        string CourseID;
        cout << "UPDATE COURSE" << endl;
        cout << "Year: "; cin >> year;
        cout << "Semester: "; cin >> semester;
        cout << "Course ID: "; cin.ignore(1); getline(cin, CourseID, '\n');
        updateCourse(year, semester, CourseID);
    }
            break;
    case 4: {
        int year;
        int semester;
        string CourseID;
        cout << "DELETE COURSE" << endl;
        cout << "Year: "; cin >> year;
        cout << "Semester: "; cin >> semester;
        cout << "Course ID: "; cin.ignore(1); getline(cin, CourseID, '\n');
        deleteCourse(year, semester, CourseID);
    }
        break;
    case 5: {
        int year;
        int semester;
        cout << "MANAGE COURSE" << endl;
        cout << "Year: "; cin >> year;
        cout << "Semester: "; cin >> semester;
        manageCourse(year, semester);
    }
        break;
    case 6: {
        return;
    }
        break;
    }
}