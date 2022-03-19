#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
using namespace std;
struct Course
{
    int ID;
    string name;
    string Instructor;
    int numbers_of_credits;
    int maximum_students;
    string first_section;
    string second_section;
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
void InnitList(List& l);
Node* CreatNode(Course course);
void Add_Course(List& l, const Course& course);
void AddCourse(List& l);
void Read_My_Course_From_TXT(List& l);
void Show_My_course(List l);
void Remove_A_Course(List& l);
void Menu(List& l);