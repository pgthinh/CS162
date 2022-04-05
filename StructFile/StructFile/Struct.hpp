#ifndef Struct_hpp
#define Struct_hpp

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <direct.h>

using namespace std;

struct Time {
    int day;
    int month;
    int year;
    Time(int day, int month, int year) : day(day), month(month), year(year) {};
    Time() {};
};
struct Year {
    int NumberOfYear;
    Year* previous_Year = NULL;
    Year* next_Year = NULL;
};
struct Semester {
    int Year;
    int TheOrderOfSemester; // 1,2,3
    Time StartDate;
    Time EndDate;
    Semester* previous_Semester = NULL;
    Semester* next_Semester = NULL;
    Semester(int year, int term, Time start, Time end) : Year(year), TheOrderOfSemester(term), StartDate(start), EndDate(end) {};
};
struct Course {
    string CourseID;
    string CourseName;
    string TeacherName;
    int NumberOfCredits;
    int MaxNumOfStudent;
    string FirstDayOfWeek; // 1.Sun 2.Mon 3.Tue 4.Wed 5.Thu 6.Fri 7.Sat
    string FirstSessionOfWeek; // 1.S1 2.S2 3.S3 4.S4
    string SecondDayOfWeek; // 1.Sun 2.Mon 3.Tue 4.Wed 5.Thu 6.Fri 7.Sat ( > the first day)
    string SecondSessionOfWeek; // 1.S1 2.S2 3.S3 4.S4 (> the first session)
    Course* previous_Course = NULL;
    Course* next_Course = NULL;
    Course(string CourseID, string CourseName, string TeacherName, int NumberOfCredits, int MaxNumOfStudent, string FirstDayOfWeek, string FirstSessionOfWeek, string SecondDayOfWeek, string SecondSessionOfWeek) :
    CourseID(CourseID), CourseName(CourseName), TeacherName(TeacherName), NumberOfCredits(NumberOfCredits), MaxNumOfStudent(MaxNumOfStudent), FirstDayOfWeek(FirstDayOfWeek), FirstSessionOfWeek(FirstSessionOfWeek), SecondDayOfWeek(SecondDayOfWeek), SecondSessionOfWeek(SecondSessionOfWeek)
    {};
    Course() {};
};
struct Class {
    string ClassId;
    Class* previous_Class = NULL;
    Class* next_Class = NULL;
};
struct Mark {
	float totalMark;
	float finalMark;
	float midtermMark;
	float otherMark;
    Mark* previous_Mark = nullptr;
    Mark* next_Mark = nullptr;

	Mark(float totalMark, float finalMark, float midtermMark, float otherMark) :
		totalMark(totalMark), finalMark(finalMark), midtermMark(midtermMark), otherMark(otherMark) {};
	Mark() {};
};
struct Student {
    int No;
    string ID; // Username when login to the system
    string Password;
    string Name;
    string Gender;
    Time Dob;
    string socialID;
    string className;
    Student* previous_Student = NULL;
    Student* next_Student = NULL;
    Mark mark;
    Student(int No, string ID, string Password, string Name, string Gender, Time Dob, string socialID, string className, Mark mark) :
        No(No), ID(ID), Name(Name), Gender(Gender), Dob(Dob), socialID(socialID), className(className), mark(mark) {};
    Student() {};
};

struct User{
    string username;
    string password;
    string role;
    User(string username, string password, string role) : username(username), password(password), role(role) {};
};

// Functions used to delete doubly linked list.
void DeleteClassList(Class*& classList);
void DeleteStudentList(Student*& student);
void DeleteCourseList(Course* &courseList);
void DeleteMarkList(Mark*& mark);
// Functions used to delete doubly linked list.
#endif /* Struct_hpp */
