#include <iostream>
#include "Struct.hpp"
using namespace std;

void DeleteClass(Class*& class){
    while(class){
        Class* temp = class;
        class = class->next_Class;
        delete temp;
    }
}
void DeleteStudent(Student*& student){
    while(student){
        Student* temp = student;
        student = student->next_Student;
        delete temp;
    }
}
