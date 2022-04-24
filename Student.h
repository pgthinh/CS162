#ifndef Student_h
#define Student_h

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Struct.hpp"
#include "supportfunction.h"
#include "Login.h"
using namespace std;
struct Node
{
    Course course;
    Node* pNext = NULL;
};
struct List
{
    Node* pHead = NULL;
    Node* pTail = NULL;
};

void InnitList(List& l);
Node* CreatNode(Course course);
void Add_Course(List& l, const Course& course);
void AddCourse(List& l, int year, int semester);
void Read_My_Course_From_TXT(List& l, string& path, int& year, int& semester, string student_id);
void Show_My_course(const List& l);
void Remove_A_Course(List& l);
void My_Score(const List& l, string ID, int year, int semester);
void Write_To_My_Course(const List& l, string path);
void Show_Profile(string ID);
void Menu(List& l, string& path, int year, int semester, string ID);
void deleteList(List& l);
#endif