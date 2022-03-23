#include "Semester.h"

void createAndSetCurrentSemester(int year, int term, Time start, Time end) {
	string path = "DATA/" + to_string(year) + '/' + to_string(term) + "/info.txt";
	ofstream fout(path);
	fout << year << '\n';
	fout << term << '\n';
	fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
	fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
	fout.close();

	path = "DATA/cache/currentSemester.txt";
	fout.open(path);
	fout << year << '\n';
	fout << term << '\n';
	fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
	fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
	fout.close();

	path = "DATA/" + to_string(year) + '/' + to_string(term);
	_mkdir(path.c_str());
	path = "DATA/" + to_string(year) + '/' + to_string(term) + "/courses";
	_mkdir(path.c_str());
	path = "DATA/" + to_string(year) + '/' + to_string(term) + "/students";
	_mkdir(path.c_str());


	path = "csvFile/" + to_string(year) + '/' + to_string(term);
	_mkdir(path.c_str());
}
Semester getCurrentSemester() {
	int year;
	int term; 
	int startday, startmonth, startyear;
	int endday, endmonth, endyear;
	
	string path = "DATA/cache/currentSemester.txt";
	ifstream fin(path);
	fin >> year;
	fin >> term;
	fin >> startday >> startmonth >> startyear;
	fin >> endday >> endmonth >> endyear;
	fin.close();

	return Semester(year, term, Time(startday, startmonth, startyear), Time(endday, endmonth, endyear));
}
void addStudentToSemester(Student*& students) {
	Semester semester = getCurrentSemester();
	int year = semester.Year;
	int term = semester.TheOrderOfSemester;

	Student* student_cur = students;

	while(student_cur){
		string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + student_cur->ID;
		_mkdir(path.c_str());
		student_cur = student_cur->next_Student;
	}
}