#include "Struct.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

Semester getCurrentSemester();
Course getCurrentCourse();
// Common Function
void WriteFileCurrentCourse(Course* course);
void updateCurrentCourse();
void WriteFileCourseList(int year, int semester, Course* courseList);
void printCourseInformation(Course* course);
void printCourseList(Course* courseList);
void deleteCourseList(Course* courseList);
// Main Functions
void setCourseRegistration(Time start, Time end);
void getCourseRegistration(Time &start, Time &end);
void setCourseInformation(Course &course);
void addCourse();
void getCourseList(int year, int semester, Course* &courseList);
void updateCourse();
void deleteCourse();
void viewCourseMangementMenu();
void getCourseStudentList(int year, int semester, string CourseID, Student* &studentList);
void viewCourseStudent(Student* student);
void viewCourseStudentList();

void getMarkOfCourse();


void exportScoreboard();
void importScoreboard();
void viewScoreboard():


void manageCourse();