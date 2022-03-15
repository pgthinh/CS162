#include "supportfunction.h"
#include "Login.h"
#include <iostream>
#include <string>
#include "Console.h"
#include "Login.h"
#include <fstream>
using namespace std;

void Loading(void)
{
    cout << "\n\n\n\n\n\n";
    cout << "\n\n\n\t\t\t\t\t\tCOURSE MANAGEMENT SYSTEM";
    cout << "\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\t\t\t";
    cout << "Loading...\n";

    cout << "\n"; for (int rep = 1; rep <= 120; rep++) cout << "_"; cout << endl;
    cout << "\n\n"; for (int rep = 1; rep <= 120; rep++) cout << "_"; cout << endl << endl;

    gotoxy(0, 15);

    cout << "\n\n\n\n\n  ";
    for (int rep = 1; rep <= 5; rep++) { cout << char(219); delay(60); }
    for (int rep = 1; rep <= 10; rep++) { cout << char(219); delay(50); }
    for (int rep = 1; rep <= 25; rep++) { cout << char(219); delay(40); }
    for (int rep = 1; rep <= 76; rep++) { cout << char(219); delay(15); }


    delay(700);

    clrscr();
    Beep(700, 100);
}
void Heading()
{
    ifstream f;
    f.open("CurrentSemester.txt");
    int year; int term;
    f >> year >> term;
    f.close();

    User account;
    f.open("CurrentAccount.txt");
    f >> account.id >> account.username >> account.password >> account.role;
    f.close();

    cout << "\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(219); cout << endl;
    cout << "\n\t\t\t\t\t\tCOURSE MANAGEMENT SYSTEM";
    cout << "\n\t\t\t\t         Year: " << year << " - " << year + 1;
    cout << "\t   Semester " << term;
    if (term == 1) cout << "(Fall)"; else
        if (term == 2) cout << "(Summer)"; else
            if (term == 3) cout << "(Autumn)";
            else cout << "(NULL)";
    if (account.role == "Staff") cout << "\n\t\t\t\t\t\t   Logged in as: ADMIN\n\n";
    else cout << "\n\t\t\t\t\t\t   Logged in as: " << account.username << "\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(219); cout << endl;
}


