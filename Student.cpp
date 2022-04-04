#include "Student.h"

int main()
{
    List l;
    InnitList(l);
    ifstream FileIn;
    FileIn.open("Myscoure.txt", ios_base::in);
    int number;
    FileIn >> number;
    if (number != 0)
    {
        Read_My_Course_From_TXT(l);
    }
    FileIn.close();
    Menu(l);
    return 0;
}

