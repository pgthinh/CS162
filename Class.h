#ifndef HEADER_CLASS_INCLUDED
#define HEADER_CLASS_INCLUDED

#include "Struct.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
#include "SchoolYear.h"
#include "Semester.h"
#include "supportfunction.h"
using namespace std;

void createClass(string className);
void getClasses(Class*& first_class);
void setCurrentClass(string className);
string getCurrentClass();

void addStudents(string className,Student*& students);
void importStudents(string className,Student*& students);

void getStudentScoreboard(int year, int term, string studentID, Course*& courseList, Mark*& mark);
float getStudentGPA(string studentID, int year, int term);

void ClassMenu();

#endif