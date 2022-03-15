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
void setCourseRegistration(Time start, Time end);
void getCourseRegistration(Time &start, Time &end);
void setCourseInformation(Course &course);
void addCourse();