#ifndef UPDATERESULT_H
#define UPDATERESULT_H

#include "struct.hpp"
#include <fstream>
#include <string>
using namespace std;
bool Find_Course(string& CourseId);
bool Find_ID(string& CourseID, string& student_id);
Mark* getInitialMarkOfStudent(string& CourseID,string& studentID);
Mark* markAfterUpdate(Mark*& mark);
void ChangeMarkFileAfterUpdate(Mark& changeMark,string& CourseID,string& studentID);

#endif