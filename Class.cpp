#include "Class.h"
 
// 1. tạo lớp mới 
 void createClass(string className){
    string path = "CLASS/" + className;
    _mkdir(path.c_str());
    
    path="CLASS/classList.txt";
    ofstream fout;
	fout.open(path, std::fstream::app);
    fout << className << endl;
    fout.close();
}
// 2. lấy list các class trong classList.txt 
void getClasses(Class*& first_class){
    string path = "CLASS/classList.txt";
    ifstream fin(path);
    first_class = new Class;
    Class* class_cur = first_class;
    while(fin >> class_cur->ClassId){
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
void setCurrentClass(string className){
    string path = "DATA/cache/currentClass.txt";
    ofstream fout(path);
    fout << className;
    fout.close();
}
// 4. lấy tên của class đang truy cập
string getCurrentClass(){
    string className;
    string path = "DATA/cache/currentClass.txt";
    ifstream fin(path);
    fin >> className;
    fin.close();
    return className;
}
// 5. thêm học sinh vào trong class từ csv file 
void addStudents(string className,Student*& students){
    importStudents(className,students);
    string path = "CLASS/" + className + "/studentList.txt";
    ofstream fout(path);
    Student* student_cur = students; 
    while(student_cur){
        fout << student_cur->ID << endl;
        /*addAccount(User(student_cur->ID,student_cur->SocialID,"student",className));*/
        student_cur = student_cur->next_Student; 
    }
    fout.close();
    student_cur = students;
    while(student_cur){
        path = "CLASS/"+ className + "/" + student_cur->ID + ".txt";
        fout.open(path);
        fout << student_cur->No << endl;
        fout << student_cur->ID << endl;
        fout << student_cur->Name << endl;
        fout << student_cur->Gender << endl;
        fout << student_cur->Gender << endl;
        fout << student_cur->Dob.day << student_cur->Dob.month << student_cur->Dob.year << endl;
        fout << student_cur->socialID << endl;
        fout.close();
        student_cur = student_cur->next_Student;
    }
}
// 6. lấy thông tin học sinh trong class từ csv file -> add students + view students cho staff và học sinh
void importStudents(string className,Student*& students){
    Student* student_cur = students;
    string path = "csvFile/classes/" + className + ".csv";
    ifstream fin; fin.open(path, ios::in);
    string sub; getline(fin,sub);
    while( fin >> student_cur->No) {
         fin.ignore();
         getline(fin,student_cur->ID,',');
         getline(fin,student_cur->Name,',');
         getline(fin,student_cur->Gender,',');
         fin >> student_cur->Dob.day; fin.ignore();
         fin >> student_cur->Dob.month; fin.ignore();
         fin >> student_cur->Dob.year; fin.ignore();
         getline(fin,student_cur->socialID,'\n');

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
// 7. Lấy list ID của các học sinh trong 1 class 
void getStudentList(string className, Student*& studentList) {
	string path = "CLASS/" + className + "/studentList.txt";
	ifstream fin(path);
	Student* studentList_cur = studentList;
	while (fin >> studentList_cur->ID){
         studentList_cur->next_Student = new Student;
         studentList_cur->next_Student->previous_Student = studentList_cur;
         studentList_cur = studentList_cur->next_Student;
    }
    Student* temp = studentList_cur;
    studentList_cur = studentList_cur->previous_Student;
    studentList_cur->next_Student = nullptr;
    delete temp;
	fin.close();
}
// 8. Lấy thông tin học sinh trong 1 class từ file txt
void getStudents(string className,Student*& students){
    Student* studentList = new Student;
    getStudentList(className,studentList);

    Student* studentList_cur = studentList;

    Student* student_cur = students;
    while(studentList_cur){
        string path = "CLASS/"+ className + "/" + studentList->ID + ".txt";
        ifstream fin(path);
        fin.ignore();
        fin >> student_cur->No;
        fin.ignore();
        getline(fin,student_cur->ID);
        getline(fin,student_cur->Name);
        getline(fin,student_cur->Gender);
        fin >> student_cur->Dob.day >> student_cur->Dob.month >> student_cur->Dob.year;
        fin.ignore();
        getline(fin,student_cur->socialID);
        fin.close();

        student_cur->next_Student = new Student;
        student_cur->next_Student->previous_Student = student_cur;
        student_cur = student_cur->next_Student;

        studentList_cur = studentList_cur->next_Student;
    }
    Student* temp = student_cur;
    student_cur = student_cur->previous_Student;
    student_cur->next_Student = nullptr;
    delete temp;
    DeleteStudentList(studentList);
}
// VIEW SCOREBOARD
// 9. Lấy list course và list điểm tương ứng với từng course, của 1 học sinh 
void getStudentScoreboard(int year, int term, string studentID, Course*& courseList, Mark*& mark) {
    Mark* mark_cur = mark;
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
float getStudentGPA(string studentID, string className) {
    string path = "DATA/" + to_string(getCurrentYear()) + "/" + to_string(getCurrentSemester().TheOrderOfSemester) + "/students/" + studentID + "/marks.txt";
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
