#include <iostream>
#include "FindAndGet_ID.h"
bool Find_Course(string CourseId)
{
	Course* first_course = new Course;
	Course* course_cur = first_course;
	string path = 'Data /' + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester()) + '/courses/courseList.txt';
	ifstream fin(path);
	fin >> course_cur->CourseID;
	while (!fin.eof()) {
		course_cur->next_course = new Course;
		course_cur = course_cur->next_course;
		fin >> course_cur->CourseID;
	}
	course_cur->next_course = nullptr;
    fin.close();
	course_cur = first_course;
	while (course_cur) {
		if (course_cur->CourseID == CourseID) {
			return true;
		}
		course_cur = course_cur->next_course;
	}
	return false;
}
bool Find_ID(string CourseID, string student_id)
{
	if (!Find_Course(CourseID)) return false;
	string id;
	string path = 'Data /' + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester()) + '/courses/' + CourseID + '/StudentIDList.txt';
	ifstream fin(path);
	while (fin >> id) {
		if (id == student_id) break;
	}
	fin.close();
	if (id == student_id) return true;
	return false;
}

