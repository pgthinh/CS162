#include <iostream>
#include "FindAndGet_ID.h"
bool Find_Course(string CourseId)
{
	Course* first_course = new Course;
	Course* course_cur = first_course;
	string path = 'DATA /' + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester()) + '/courses/courseList.txt';
	ifstream fin(path);
	while (fin >> course_cur->CourseID) {
		course_cur->next_Course = new Course;
		course_cur->next_Course->previous_Course = course_cur;
		course_cur = course_cur->next_course;
	}
	Course* temp = course_cur;
	course_cur = course_cur->previous_Course;
	course_cur->next_Course = nullptr;
	delete temp;
    fin.close();
	course_cur = first_course;
	while (course_cur) {
		if (course_cur->CourseID == CourseID) {
			return true;
		}
		course_cur = course_cur->next_Course;
	}
	return false;
}
bool Find_ID(string CourseID, string student_id)
{
	if (!Find_Course(CourseID)) return false;
	string id;
	string path = 'Data /' + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester()) + '/courses/' + CourseID + '/Students.txt';
	ifstream fin(path);
	while (fin >> id) {
		if (id == student_id) break;
	}
	fin.close();
	if (id == student_id)  return true;
	return false;
}

