

#ifndef Struct_hpp
#define Struct_hpp

#include <iostream>

using namespace std;

struct Time {
    int day;
    int month;
    int year;
};
struct Year {
    int NumberOfYear;
    Year* previous_Year;
    Year* next_Year;
};
struct Semester {
    int TheOrderOfSemester; // 1,2,3
    Time StartDate;
    Time EndDate;
    Semester* previous_Semester;
    Semester* next_Semester;
};
struct Course {
    string CourseID;
    string CourseName;
    string TeacherName;
    int NumberOfCredits;
    int MaxNumOfStudent;
    int FirstDayOfWeek; // 1.Sun 2.Mon 3.Tue 4.Wed 5.Thu 6.Fri 7.Sat
    int FirstSessionOfWeek; // 1.S1 2.S2 3.S3 4.S4
    int SecondDayOfWeek; // 1.Sun 2.Mon 3.Tue 4.Wed 5.Thu 6.Fri 7.Sat ( > the first day)
    int SecondSessionOfWeek; // 1.S1 2.S2 3.S3 4.S4 (> the first session)
    Course* previous_Course; 
    Course* next_Course;
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

    User(string ID, string Password, string Name, string Gender) :
		ID(ID), Password(Password), Name(Name), Gender(Gender) {};
	User() {};
};

struct User{
    string username;
    string password;
    string role;
};

#endif /* Struct_hpp */
