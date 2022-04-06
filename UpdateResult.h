#ifndef UPDATERESULT_H
#define UPDATERESULT_H

#include "Struct.hpp"
#include "Semester.h"
#include "SchoolYear.h"
#include <fstream>

using namespace std;
bool Find_Course(int year, int term, string CourseId);
bool Find_ID(int year, int term, string CourseID, string student_id);
Mark getInitialMarkOfStudent(int year, int term, string CourseID, string studentID);
Mark markAfterUpdate(Mark& score);
void ChangeMarkFileAfterUpdate(int year, int term, Mark& changeMark, string CourseID, string studentID);

#endif
