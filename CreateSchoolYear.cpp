#include "CreateSchoolYear.h"
#include <iostream>
#include <fstream>

bool readInt(int& number) {
	fflush(stdin);
	string input;
	cin >> input;
	for (char c : input) if (c < '0' || '9' < c) return 0;
	number = stoi(input);
	return 1;
}

void createSchoolYear(){
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t     ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CREATE SCHOOL YEAR "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t      Year(yyyy)         : \n\n";
    cout << "\t\t\t\t\t      Action(commit/back): \n\n\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    int year; gotoxy(67, 12); if (!readInt(year) || year<1000 || 9999<year){
        cout << "\n\n\n\t\t\t\t\t\t      Invalid input";
        delay(1500);
        createSchoolYear();
    }
    do {
        string confirm; gotoxy(67, 14);
        fflush(stdin);
        cin >> confirm;
        if (confirm == "back") return; else
            if (confirm == "commit") {
                ofstream f;
                f.open("CurrentYear.txt");
                f << year;
                f.close();
                cout << "\n\t\t\t\t\t    Year has been created successfully";
                delay(1500); return;
            }
        gotoxy(67, 14); for (char c : confirm) cout << ' ';
    } while (true);
}
bool readDate(Time& date) {
	// dd/mm/yyyy
	fflush(stdin);
	string input;
	cin >> input;
	if (input.size() != 10) return 0;
	for(int i=0; i<10; ++i)
		if (i == 2 || i == 5) {
			if (input[i] != '/') return 0;
		}
		else {
			if (input[i] < '0' || '9' < input[i]) return 0;
		}
    date.day = stoi(input.substr(0,2));
    date.month = stoi(input.substr(3, 2));
    date.year = stoi(input.substr(6, 4));

	return 1;
}

void createSemester() {
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t      ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CREATE SEMESTER "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t      Semester(1/2/3)       : \n\n";
    cout << "\t\t\t\t\t      Start date(dd/mm/yyyy): \n\n";
    cout << "\t\t\t\t\t      End date(dd/mm/yyyy)  : \n\n";
    cout << "\t\t\t\t\t      Action(commit/back)   : \n\n\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    int semester; Time start, end;
    gotoxy(70, 12); if (!readInt(semester) || semester<1 || 3<semester) {
        gotoxy(53, 20); cout << "Invalid input";
        delay(1500);
        createSemester();
        return;
    }
    gotoxy(70, 14); if (!readDate(start)) {
        gotoxy(53, 20); cout << "Invalid input";
        delay(1500);
        createSemester();
        return;
    }
    gotoxy(70, 16); if (!readDate(end)){
        gotoxy(53, 20); cout << "Invalid input";
        delay(1500);
        createSemester();
        return;
    }

    do {
        string confirm; gotoxy(70, 18);
        fflush(stdin);
        cin >> confirm;
        if (confirm == "back") return; else
            if (confirm == "commit") {
                ifstream fin;
                fin.open("CurrentYear.txt");
                int year; fin >> year;
                fin.close();
                ofstream fout;
		fout.open("CurrentYear.txt");
                fout << year << '\n' << semester << '\n' << start.day << " " << start.month << " " << start.year <<'\n';
                fout << end.day << " " << end.month << " " << end.year;
                cout << "\n\t\t\t\t\t   Semester has been created successfully";
                fout.close();
                delay(1500); return;
            }
        gotoxy(70, 18); for (char c : confirm) cout << ' ';
    } while (true);

}

