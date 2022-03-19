#ifndef HEADER_CLASS_INCLUDED
#define HEADER_CLASS_INCLUDED

#include "Struct.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
using namespace std;
struct StudentList{
      string ID;
      StudentList* next_Student = nullptr;
      StudentList* previous_Student = nullptr;
};

void createClass(string className);
void getClasses(Class*& first_class);
void setCurrentClass(string className);
string getCurrentClass();

void addStudents(string className,Student*& students);
void getStudents(string className,Student*& students);
void getStudentList(string className, StudentList*& studentList)
void importStudents(string className,Student*& students);

void Delete_StudentList_List(StudentList*& studentList);
#endif