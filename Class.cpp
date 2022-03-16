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
    string path = "csvFile/classes/" + className + ".csv";
    ifstream fin(path);
    string sub; getline(fin,sub);
    while( fin >> students->No) {
         fin.ignore();
         getline(fin,students->id,',');
         getline(fin,students->name,',');
         getline(fin,students->gender,',');
         fin >> students->dob.day; fin.ignore();
         fin >> students->dob.month; fin.ignore();
         fin >> students->dob.year; fin.ignore();
         getline(fin,socialID,'\n');
         
         students->next_Student = new Student;
         students = students->next_Student;
    }
    Student* temp = students;
    students = students->previous_Student;
    delete temp;
    fin.close();
}