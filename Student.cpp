#include <iostream>
#include "student.h"
using namespace std;

int main()
{
    List l;
    InnitList(l);
    string path;
    Read_My_Course_From_TXT(l, path);
    Menu(l,path);
    return 0;
}
