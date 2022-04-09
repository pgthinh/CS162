#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;
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
struct Node
{
    Course course;
    Node* pNext;
};
struct List
{
    Node* pHead;
    Node* pTail;
};
struct Time {
    int day;
    int month;
    int year;
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

void InnitList(List& l);
Node* CreatNode(Course course);
void Add_Course(List& l, const Course& course);
void AddCourse(List& l);
void Read_My_Course_From_TXT(List& l);
void Show_My_course(const List &l);
void Remove_A_Course(List& l);
void Menu(List& l);
void My_Score(const List &l);
void Write_To_My_Course(const List& l);
void Show_Profile();
