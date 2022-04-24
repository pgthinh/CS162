#include "Class.h"
#include "Console.h"
#include <iostream>
using namespace std;
//1.Tạo lớp
void createClass(string className) {
    string path = "CLASS/" + className;
    _mkdir(path.c_str());

    path = "CLASS/classList.txt";
    ofstream fout;
    fout.open(path, std::fstream::app);
    if (fout.eof()) fout << className;
    else fout << '\n' << className;
    fout.close();
}
// 2. lấy list các class trong classList.txt
void getClasses(Class*& first_class) {
    string path = "CLASS/classList.txt";
    ifstream fin(path);
    first_class = new Class;
    Class* class_cur = first_class;
    while (fin >> class_cur->ClassId) {
        class_cur->next_Class = new Class;
        class_cur->next_Class->previous_Class = class_cur;
        class_cur = class_cur->next_Class;
    }
    Class* temp = class_cur;
    class_cur = class_cur->previous_Class;
    class_cur->next_Class = nullptr;
    delete temp;
    fin.close();
}
// 3. chọn lớp để truy cập
void setCurrentClass(string className) {
    string path = "DATA/cache/currentClass.txt";
    ofstream fout(path);
    fout << className;
    fout.close();
}
// 4. lấy tên của class đang truy cập
string getCurrentClass() {
    string className;
    string path = "DATA/cache/currentClass.txt";
    ifstream fin(path);
    fin >> className;
    fin.close();
    return className;
}
// 5. thêm học sinh vào trong class từ csv file
void addStudents(string className, Student*& studentList) {
    importStudents(className, studentList);
    string path = "CLASS/" + className + "/studentList.txt";
    ofstream fout; fout.open(path);
    Student* student_cur = studentList;
    while (student_cur) {
        fout << student_cur->ID << endl;
        student_cur = student_cur->next_Student;
    }
    fout.close();
    student_cur = studentList;
    while (student_cur) {
        path = "CLASS/" + className + "/" + student_cur->ID + ".txt";
        fout.open(path);
        fout << student_cur->No << endl;
        fout << student_cur->ID << endl;
        fout << student_cur->Name << endl;
        fout << student_cur->Gender << endl;
        fout << student_cur->Dob.day << ' ' << student_cur->Dob.month << ' ' << student_cur->Dob.year << endl;
        fout << student_cur->socialID;
        fout.close();
        student_cur = student_cur->next_Student;
    }
}
// 6. lấy thông tin học sinh trong class từ csv file -> add students + view students cho staff và học sinh
void importStudents(string className, Student*& students) {
    students = new Student;
    Student* student_cur = students;

    string path = "csvFile/classes/" + className + ".csv";
    ifstream fin; fin.open(path, ios::in);
    string sub; getline(fin, sub, '\n');
    while (fin >> student_cur->No) {
        fin.ignore();
        getline(fin, student_cur->ID, ',');
        getline(fin, student_cur->Name, ',');
        getline(fin, student_cur->Gender, ',');
        fin >> student_cur->Dob.day; fin.ignore();
        fin >> student_cur->Dob.month; fin.ignore();
        fin >> student_cur->Dob.year; fin.ignore();
        getline(fin, student_cur->socialID, '\n');

        fstream fout("CLASS/" + className + "/" + student_cur->ID + ".txt");
        fout << student_cur->No << "\n" << student_cur->ID << "\n" << student_cur->Name << "\n" << student_cur->Gender << "\n";
        fout << student_cur->Dob.day << " " << student_cur->Dob.month << " " << student_cur->Dob.year << "\n" << student_cur->socialID;
        fout.close();

        student_cur->next_Student = new Student;
        student_cur->next_Student->previous_Student = student_cur;
        student_cur = student_cur->next_Student;
    }
    Student* temp = student_cur;
    student_cur = student_cur->previous_Student;
    student_cur->next_Student = nullptr;
    delete temp;
    fin.close();
}
// 7. lấy list id của các học sinh trong 1 class
void getstudentlist(string classname, Student*& studentlist) {
    string path = "class/" + classname + "/studentlist.txt";
    ifstream fin(path);
    Student* studentlist_cur = studentlist;
    while (fin >> studentlist_cur->ID) {
        studentlist_cur->next_Student = new Student;
        studentlist_cur->next_Student->previous_Student = studentlist_cur;
        studentlist_cur = studentlist_cur->next_Student;
    }
    Student* temp = studentlist_cur;
    studentlist_cur = studentlist_cur->previous_Student;
    studentlist_cur->next_Student = nullptr;
    delete temp;
    fin.close();
}
// VIEW SCOREBOARD
// 9. Lấy list course và list điểm tương ứng với từng course, của 1 học sinh
void getStudentScoreboard(int year, int term, string studentID, Course*& courseList, Mark*& markList) {
    courseList = new Course; markList = new Mark;
    Mark* mark_cur = markList;
    Course* courseList_cur = courseList;
    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + studentID + "/marks.txt";
    ifstream fin(path);
    while (fin >> courseList_cur->CourseID >> mark_cur->totalMark >> mark_cur->finalMark >> mark_cur->midtermMark >> mark_cur->otherMark) {
        courseList_cur->next_Course = new Course;
        courseList_cur->next_Course->previous_Course = courseList_cur;
        courseList_cur = courseList_cur->next_Course;

        mark_cur->next_Mark = new Mark;
        mark_cur->next_Mark->previous_Mark = mark_cur;
        mark_cur = mark_cur->next_Mark;
    }
    Course* temp1 = courseList_cur;
    courseList_cur = courseList_cur->previous_Course;
    courseList_cur->next_Course = nullptr;
    delete temp1;

    Mark* temp2 = mark_cur;
    mark_cur = mark_cur->previous_Mark;
    mark_cur->next_Mark = nullptr;
    delete temp2;
}
//11. Tính overall GPA của học sinh
float getStudentGPA(string studentID, int year, int term) {
    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + studentID + "/marks.txt";
    ifstream fin(path);
    Mark mark; string course;
    float sum = 0;
    int cnt = 0;
    while (fin >> course >> mark.totalMark >> mark.finalMark >> mark.midtermMark >> mark.otherMark) {
        sum += mark.totalMark;
        cnt += 1;
    }
    fin.close();
    float GPA = cnt > 0 ? sum / cnt : 0;
    return GPA / 10 * 4;
}

void ClassMenu() {
    while (true) {
        clrscr(); Heading();
        cout << "\n\n\t\t\t\t\t\t";
        for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CLASS MENU "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
        cout << "\n\n";
        cout << "\t\t\t\t\t      1. Create classes\n\n";
        cout << "\t\t\t\t\t      2. Choose a class to manage\n\n";
        cout << "\t\t\t\t\t      3. Go back\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

        fflush(stdin);
        int choice; string className;
        cout << "\n\t\t\t\t\t\t  Selection : "; cin >> choice;
        switch (choice) {
        case 1: {
            clrscr(); Heading();
            cout << "\n\n\t\t\t\t\t      ";
            for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CREATE CLASS "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
            cout << "\n\n";
            cout << "\t\t\t\t\t\tClass name : ";
            cin >> className;
            createClass(className);
            SetColor(10);
            cout << "\n\t\t\t\t\t        Create successfully ";
            SetColor(15);
            delay(1500);
            break;
        }
        case 2: {
            int select = 0;
            while (select != 4) {
                clrscr(); Heading();
                cout << "\n\n\t\t\t\t\t\t   ";
                for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CLASS MANAGE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                cout << "\n\n";
                cout << "\t\t\t\t\t\t     1. Add students\n\n";
                cout << "\t\t\t\t\t\t     2. View students\n\n";
                cout << "\t\t\t\t\t\t     3. View scoreboard\n\n";
                cout << "\t\t\t\t\t\t     4. Go back\n\n";
                for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
                cout << "\n\t\t\t\t\t\t     Selection : "; cin >> select;
                switch (select) {
                case 1: {
                    clrscr(); Heading();
                    cout << "\n\n\t\t\t\t\t\t   Class name : ";
                    cin >> className;
                    Student* studentList;
                    addStudents(className, studentList);
                    DeleteStudentList(studentList);
                    SetColor(10);
                    cout << "\n\n\t\t\t\t\t     Add successfully from csv file";
                    SetColor(15);
                    delay(1500);
                    break;
                }
                case 2: {
                    clrscr(); Heading();
                    cout << "\n\n\t\t\t\t\t\t   Class name : ";
                    cin >> className;
                    cout << "\n\n\t\t\t\t\t\t   ";
                    Student* studentList;
                    addStudents(className, studentList);
                    clrscr(); Heading();
                    cout << "\n\n\t\t\t\t\t\t   ";
                    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " " << className << " "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                    cout << "\n\n";

                    gotoxy(10, 12); cout << "No";
                    gotoxy(15, 12); cout << "Student ID";
                    gotoxy(30, 12); cout << "Full Name";
                    gotoxy(70, 12); cout << "Gender";
                    gotoxy(80, 12); cout << "Date of birth";
                    gotoxy(100, 12); cout << "Social ID";

                    Student* student_cur = studentList;
                    int i = 0;
                    while (student_cur) {
                        gotoxy(10, 14 + i * 2); cout << student_cur->No << ". ";
                        gotoxy(15, 14 + i * 2); cout << student_cur->ID;
                        gotoxy(30, 14 + i * 2); cout << student_cur->Name;
                        gotoxy(70, 14 + i * 2); cout << student_cur->Gender;
                        gotoxy(80, 14 + i * 2); cout << student_cur->Dob.day << "-" << student_cur->Dob.month << "-" << student_cur->Dob.year;
                        gotoxy(100, 14 + i * 2); cout << student_cur->socialID;
                        i++;
                        student_cur = student_cur->next_Student;
                    }
                    DeleteStudentList(studentList);
                    _getch();
                    break;
                }
                case 3: {
                    clrscr(); Heading();
                    cout << "\n\n\t\t\t\t\t\t ";
                    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                    cout << "\n\n";
                    int year, semester;
                    cout << "\n\t\t\t\t\t\t   Year : ";
                    cin >> year;
                    cout << "\n\t\t\t\t\t\t   Semester : ";
                    cin >> semester;
                    cout << "\n\t\t\t\t\t\t   Class name : "; cin.ignore();
                    cin >> className;
                    Student* students;
                    importStudents(className, students);
                    Student* student_cur = students;

                    clrscr(); Heading();
                    cout << "\n\n\t\t\t\t\t\t ";
                    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                    cout << "\n\n";
                    int i = 0;
                    while (student_cur) {
                        cout.precision(2);
                        Course* courseList; Mark* markList;
                        getStudentScoreboard(year, semester, student_cur->ID, courseList, markList);

                        Course* course_cur = courseList; Mark* mark_cur = markList;
                        gotoxy(20, 14 + i * 3); cout << i + 1 << ". ";
                        gotoxy(25, 14 + i * 3); cout << student_cur->Name;
                        gotoxy(25, 15 + i * 3); cout << student_cur->ID;

                        int j = 0;
                        while (j != 5) {
                            if (course_cur) {
                                gotoxy(47 + j * 8, 14 + i * 3); cout << course_cur->CourseID;
                                gotoxy(47 + j * 8, 15 + i * 3); cout << fixed << mark_cur->totalMark;
                                course_cur = course_cur->next_Course;
                                mark_cur = mark_cur->next_Mark;
                            }
                            else {
                                gotoxy(47 + j * 8, 14 + i * 3); cout << "----";
                                gotoxy(47 + j * 8, 15 + i * 3); cout << "----";
                            }
                            j++;
                        }

                        gotoxy(95, 14 + i * 3); cout << "Overall GPA";
                        gotoxy(95, 15 + i * 3); cout << fixed << getStudentGPA(student_cur->ID, year, semester); //overall

                        DeleteCourseList(courseList); DeleteMarkList(markList);
                        student_cur = student_cur->next_Student;
                        i++;
                    }

                    cout << "\n\n";
                    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
                    _getch();
                    DeleteStudentList(students);
                    break;
                }
                }
            }
        }
        case 3: return;
        default: SetColor(12); cout << "\n\t\t\t\t\t\tInvalid choice"; SetColor(15); delay(1500);
        }
    }
}
