#ifndef HEADER_SEMESTER_INCLUDED
#define HEADER_SEMESTER_INCLUDED

#include "Struct.hpp"
#include "schoolYear.h"


#include <fstream>
#include <iostream>
#include <string>
#include <direct.h>
using namespace std;

void createAndSetCurrentSemester(int year, int term, Date start, Date end);
Semester getCurrentSemester();
void addStudentToSemester(Student*& students);

#endif
