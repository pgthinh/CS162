#ifndef HEADER_CLASS_INCLUDED
#define HEADER_CLASS_INCLUDED

#include "struct.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
using namespace std;

void createClass(string className);
void getClasses(Class*& first_class);
void setCurrentClass(string className);
string getCurrentClass();

void addStudents(string className,Student*& students);
void importStudents(string className,Student*& students);
#endif