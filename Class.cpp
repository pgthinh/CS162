#include "Class.h"
 
 void createClass(string className){
    string path = "data/classes/" + className;
    _mkdir(path.c_str());
    
    path="data/classes/classList.txt";
    ofstream fout;
	fout.open(path, std::fstream::app);
    fout << className << endl;
    fout.close();
}
void getClasses(Class*& first_class){
    string path = "DATA/classes/classList.txt";
    ifstream fin(path);
    first_class = new Class;
    Class class_cur = first_class;
    while(fin >> class_cur->ClassID){
        class_cur->next_Class = new Class;
		class_cur->next_Class->previous_Class = class_cur;
		class_cur = class_cur->next_class;
	}
	Class* temp = class_cur;
	class_cur = class_cur->previous_Class;
	class_cur->next_Class = nullptr;
	delete temp;
    fin.close();
}
void setCurrentClass(string className){
    string path = "DATA/cache/currentClass.txt";
    ofstream fout(path);
    fout << className;
    fout.close();
}
string getCurrentClass(){
    string path = "DATA/cache/currentClass.txt";
    ifstream fin(path);
    string className; fin >> className;
    fout.close();
}
void addStudents(string className,Student*& students){
    importStudents(className,students);
    string path = "CLASS/" + className + "/studentList.txt";
    ofstream fout(path);
    Student* student_cur = students; 
    while(student_cur){
        fout << student_cur->ID << endl;
        addAccount(User(student_cur->ID,student_cur->SocialID,"student",className));
        student_cur = student_cur->next_Student; 
    }
    fout.close();
    student_cur = students;
    while(student_cur){
        path = "CLASS/"+ className + "/" + student_cur->ID + ".txt";
        fout.open(path);
        fout << student_cur->ID << endl;
        fout << student_cur->Name << endl;
        fout << student_cur->Gender << endl;
        fout << student_cur->Gender << endl;
        fout << student_cur->Dob.day << student_cur->Dob.month << student_cur->Dob.year << endl;
        fout << student_cur->SocialID << endl;
        fout.close();
        student_cur = student_cur->next_Student;
    }
}
void importStudents(string className,Student*& students){
    Student* student_cur = students;
    string path = "csvFile/classes/" + className + ".csv";
    ifstream fin(path);
    string sub; getline(fin,sub);
    while( fin >> student_cur->No) {
         fin.ignore();
         getline(fin,student_cur->id,',');
         getline(fin,student_cur->name,',');
         getline(fin,student_cur->gender,',');
         fin >> student_cur->dob.day; fin.ignore();
         fin >> student_cur->dob.month; fin.ignore();
         fin >> student_cur->dob.year; fin.ignore();
         getline(fin,student_cur->SocialID,'\n');
         
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
void getStudentList(string className, StudentList*& studentList) {
	string path = "CLASS/" + className + "/studentList.txt";
	ifstream fin(path);
	StudentList* studentList_cur = studentList;
	while (fin >> studentList_cur->ID){
         studentList_cur->next_Student = new StudentList;
         studentList_cur->next_Student->previous_Student = studentList_cur;
         studentList_cur = studentList_cur->next_Student;
    }
    StudentList* temp = studentList_cur;
    studentList_cur = studentList_cur->previous_Student;
    studentList_cur->next_Student = nullptr;
    delete temp;
	fin.close();
}
void getStudents(string className,Student*& students){
    StudentList* studentList = new StudentList;
    getStudentList(className,studentList);

    Student* student_cur = students;
    while(StudentList){
        string path = "CLASS/"+ className + "/" + StudentList->ID + ".txt";
        ifstream fin(path);
        fin.ignore();
        getline(fin,student_cur->ID);
        getline(fin,student_cur->Name);
        getline(fin,student_cur->gender);
        fin >> student_cur->Dob.day >> student_cur->Dob.month >> student_cur->Dob.year;
        fin.ignore();
        getline(fin,student_cur->SocialID);
        fin.close();

        student_cur->next_Student = new Student;
        student_cur->next_Student->previous_Student = student_cur;
        student_cur = student_cur->next_Student;

        StudentList = student_List->next_Student;
    }
    Student* temp = student_cur;
    student_cur = student_cur->previous_Student;
    student_cur->next_Student = nullptr;
    delete temp;
}
void Delete_StudentList_List(StudentList*& studentList){
    while(studentList){
        StudentList* temp = studentList;
        studentList = studentList->next_Student;
        delete temp;
    }
}