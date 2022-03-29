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
void WriteFileCourseInfoList(int year, int semester, Course* courseList);
void getCourseList(int year, int semester, Course* &courseList);
void WriteFileCourseList(int year, int semester, Course* courseList);
void printCourseInformation(Course* course);
void printCourseList(Course* courseList);
void deleteCourseList(Course* &courseList);
// Main Functions

void writeFileCourseRegistration(Time start, Time end);
void updateCourseRegistration(Time &start, Time &end);

void setCourseInformation(Course &course);
void addCourse();

void updateCourse(int year, int semester, string CourseID);

void deleteCourse(int year, int semester, string CourseID);

void viewCourseMangementMenu();

void getCourseMarkList(int year, int semester, string CourseID, Student* &studentList);
void getCourseStudentList(int year, int semester, string CourseID, Student* &studentList);
void viewCourseStudent(Student* student);
void viewCourseStudentList(Student* studentList);
void exportScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student* &studentList);
void importScoreboardOfStudentListOfCourse(int year, int semester, string CourseID, Student* studentList);
void viewScoreboard(Student* studentList);
void manageCourse();

void courseMenu();