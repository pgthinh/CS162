

#ifndef Struct_hpp
#define Struct_hpp

#include <iostream>

using namespace std;

struct Time {
    int day;
    int month;
    int year;
    Time(int day, int month, int year) : day(day), month(month), year(year) {};
};
struct Year {
    int NumberOfYear;
    Year* previous_Year;
    Year* next_Year;
};
struct Semester {
    int Year;
    int TheOrderOfSemester; // 1,2,3
    Time StartDate;
    Time EndDate;
    Semester* previous_Semester;
    Semester* next_Semester;
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
    Course* previous_Course;
    Course* next_Course;
    Course(string CourseID, string CourseName, string TeacherName, int NumberOfCredits, int MaxNumOfStudent, string FirstDayOfWeek, string FirstSessionOfWeek, string SecondDayOfWeek, string SecondSessionOfWeek) :
    CourseID(CourseID), CourseName(CourseName), TeacherName(TeacherName), NumberOfCredits(NumberOfCredits), MaxNumOfStudent(MaxNumOfStudent), FirstDayOfWeek(FirstDayOfWeek), FirstSessionOfWeek(FirstSessionOfWeek), SecondDayOfWeek(SecondDayOfWeek), SecondSessionOfWeek(SecondSessionOfWeek)
    {};
    Course() {};
};
struct Class {
    string ClassId;
    Class* previous_Class;
    Class* next_Class;
};
struct Student {
    int No;
    string ID; // Username when login to the system
    string Password;
    string Name;
    string Gender;
    Time Dob;
    Student* previous_Student;
    Student* next_Student;
    Student(int No, string ID, string Password, string Name, string Gender, Time Dob) :
		No(No), ID(ID), Password(Password), Name(Name), Gender(Gender), Dob(Dob) {};
};

struct User{
    string username;
    string password;
    string role;
    User(string username, string password, string role) : username(username), password(password), role(role) {};
};

#endif /* Struct_hpp */
