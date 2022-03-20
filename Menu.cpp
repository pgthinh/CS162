#include "Menu.h"
#include "Console.h"
#include <iostream>
#include "supportfunction.h"
#include "CreateSchoolYear.h"
#include "Login.h"

using namespace std;

void staffMenu(){
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t\t";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " FACULTY MENU "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t\t 1. Create school year\n\n";
    cout << "\t\t\t\t\t\t 2. Create semester\n\n";
    cout << "\t\t\t\t\t\t 3. Course management\n\n";
    cout << "\t\t\t\t\t\t 4. Class management\n\n";
    cout << "\t\t\t\t\t\t 5. Student management\n\n";
    cout << "\t\t\t\t\t\t 6. Change password\n\n";
    cout << "\t\t\t\t\t\t 7. Logout\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    fflush(stdin);
    int choice;
    cout << "\n\t\t\t\t\t\tEnter Your Choice : "; cin >> choice;
    switch(choice){
    case 1: {createSchoolYear(); staffMenu(); break;}
    case 2: {createSemester(); staffMenu(); break;}
    case 6: {changePassword(); staffMenu(); break;}
    case 7: {Login(); break;}
    }


}

void studentMenu(){
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t\t";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " STUDENT MENU "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t\t   1. Add a course\n\n";
    cout << "\t\t\t\t\t\t   2. Remove a course\n\n";
    cout << "\t\t\t\t\t\t   3. My courses\n\n";
    cout << "\t\t\t\t\t\t   4. My scoreboard\n\n";
    cout << "\t\t\t\t\t\t   5. Change password\n\n";
    cout << "\t\t\t\t\t\t   6. View profile\n\n";
    cout << "\t\t\t\t\t\t   7. Logout\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    fflush(stdin); int choice;
    cout << "\n\t\t\t\t\t\tEnter Your Choice : "; cin >> choice;

    switch(choice){
    case 5: {changePassword(); studentMenu(); break;}
    case 7: {Login(); break;}
    }
}
