#include <iostream>
#include "Struct.hpp"
using namespace std;

void DeleteClassList(Class*& classList){
    while(classList){
        Class* temp = classList;
        classList = classList->next_Class;
        delete temp;
    }
}
void DeleteStudentList(Student*& student){
    while(student){
        Student* temp = student;
        student = student->next_Student;
        delete temp;
    }
}
void DeleteCourseList(Course* &courseList) {
    while(courseList) {
        Course* t = courseList;
        courseList = courseList->next_Course;
        delete t;
    }
}
void DeleteMarkList(Mark*& mark){
    while(mark){
        Mark* temp = mark;
        mark = mark->next_Mark;
        delete temp;
    }
}