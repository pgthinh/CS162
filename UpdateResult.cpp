#include <iostream>
#include "UpdateResult.h"
#include "Console.h"

bool Find_Course(string& CourseId)
{
	string courseName;
	string path = "DATA/" + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester().TheOrderOfSemester) + "/course_list/courseList.txt";
	ifstream fin(path);
	while (fin >> courseName) {
		if(CourseId == courseName){
            fin.close();
            return true;
		}
	}
	fin.close();
	return false;
}
bool Find_ID(string& CourseID, string& student_id)
{
	if (!Find_Course(CourseID)) return false;
	string id; string className;
	string path = "DATA/" + to_string(getCurrentYear()) + "/" + to_string(getCurrentSemester().TheOrderOfSemester) + "/course_list/" + CourseID + "/students.txt";
	ifstream fin(path);
	while (fin >> id >> className) {
		if (id == student_id){
            fin.close();
            return true;
		}
	}
	fin.close();
	return false;
}
Mark* getInitialMarkOfStudent(string& CourseID,string& studentID){
	Mark* mark = new Mark;
	Course* course = new Course;
	string path = "DATA/" + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester().TheOrderOfSemester) + "/students/" + studentID + "/marks.txt";
	ifstream fin(path);
    while(fin >> course->CourseID >> mark->totalMark >> mark->finalMark >> mark->midtermMark >> mark->otherMark){
		if(course->CourseID == CourseID){
			break;
		}
	}
	delete course;
	fin.close();
	return mark;
}
Mark markAfterUpdate(Mark& mark){
	mark.totalMark = mark.finalMark / 10 * 5 + mark.midtermMark / 10 * 3 + mark.otherMark / 10 * 2;
	return mark;
}
void ChangeMarkFileAfterUpdate(Mark& changeMark,string& CourseID,string& studentID){
	// change in year/semester/students/studentID/marks.txt
	Mark* first_mark = new Mark; Mark* mark_cur = first_mark;
	Course* first_course = new Course; Course* course_cur = first_course;
    string path = "DATA/" + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester().TheOrderOfSemester) + "/students/" + studentID + "/marks.txt";
	ifstream fin(path);
	while(fin >> course_cur->CourseID >> mark_cur->totalMark >> mark_cur->finalMark >> mark_cur->midtermMark >> mark_cur->otherMark){
		if(course_cur->CourseID == CourseID){
			mark_cur->totalMark = changeMark.totalMark;
			mark_cur->finalMark = changeMark.finalMark;
			mark_cur->midtermMark = changeMark.midtermMark;
			mark_cur->otherMark = changeMark.otherMark;
		}
		mark_cur->next_Mark = new Mark;
		mark_cur->next_Mark->previous_Mark = mark_cur;
		mark_cur = mark_cur->next_Mark;

		course_cur->next_Course = new Course;
		course_cur->next_Course->previous_Course = course_cur;
		course_cur = course_cur->next_Course;
	}
	fin.close();

    Mark* temp1 = mark_cur;
	mark_cur = mark_cur->previous_Mark;
	mark_cur->next_Mark = nullptr;
	delete temp1;

	Course* temp2 = course_cur;
	course_cur = course_cur->previous_Course;
	course_cur->next_Course = nullptr;
	delete temp2;

	mark_cur = first_mark;  course_cur = first_course;
	ofstream fout(path);
	while(course_cur){
		fout << course_cur->CourseID << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark << endl;
		course_cur = course_cur->next_Course;
		mark_cur = mark_cur->next_Mark;
	}
	DeleteCourseList(first_course);  DeleteMarkList(first_mark);
	fout.close();

	// change in year/semester/course_list/CourseID/marks.txt
	Student* first_student = new Student;  Student* student_cur = first_student;
	first_mark = new Mark;  mark_cur = first_mark;
	path = "DATA/" + to_string(getCurrentYear()) + '/' + to_string(getCurrentSemester().TheOrderOfSemester) + "/course_list/" + CourseID + "/marks.txt";
    fin.open(path);
	while(fin >> student_cur->ID >> mark_cur->totalMark >> mark_cur->finalMark >> mark_cur->midtermMark >> mark_cur->otherMark >> student_cur->Name){
		if(student_cur->ID == studentID){
			mark_cur->totalMark = changeMark.totalMark;
			mark_cur->finalMark = changeMark.finalMark;
			mark_cur->midtermMark = changeMark.midtermMark;
			mark_cur->otherMark = changeMark.otherMark;
		}
		mark_cur->next_Mark = new Mark;
		mark_cur->next_Mark->previous_Mark = mark_cur;
		mark_cur = mark_cur->next_Mark;

		student_cur->next_Student = new Student;
		student_cur->next_Student->previous_Student = student_cur;
		student_cur = student_cur->next_Student;
	}
	fin.close();

	Mark* temp3 = mark_cur;
	mark_cur = mark_cur->previous_Mark;
	mark_cur->next_Mark = nullptr;
	delete temp3;

	Student* temp4 = student_cur;
	student_cur = student_cur->previous_Student;
	student_cur->next_Student = nullptr;
	delete temp4;

	mark_cur = first_mark;   student_cur = first_student;
	fout.open(path);
	while(student_cur){
		fout << student_cur->ID << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark << " " << student_cur->Name << endl;
		student_cur = student_cur->next_Student;
		mark_cur = mark_cur->next_Mark;
	}
	DeleteStudentList(first_student);  DeleteMarkList(first_mark);
	fout.close();
	// change in CLASS/className/StudentID_marks.txt
	/*string className; string student_id;
	path = "DATA/" + to_string(getCurrentYear()) + "/" + to_string(getCurrentSemester().TheOrderOfSemester) + "/ course_list /" + CourseID + "/students.txt";
    fin.open(path);
	while(fin >> student_id >> className){
		if(student_id == studentID) break;
	}

	Mark* initialMark = getInitialMarkOfStudent(CourseID,studentID);
	first_mark = new Mark;  mark_cur = first_mark;
	path = "CLASS/" + className + "/" + studentID + "_marks.txt";
	fin.open(path);
	while( fin >> mark_cur->totalMark){
		if(mark_cur->totalMark == initialMark->totalMark){
			mark_cur->totalMark = changeMark.totalMark;
		}
		mark_cur->next_Mark = new Mark;
		mark_cur->next_Mark->previous_Mark = mark_cur;
		mark_cur = mark_cur->next_Mark;
	}
	fin.close();
    Mark* temp5 = mark_cur;
	mark_cur = mark_cur->previous_Mark;
	mark_cur->next_Mark = nullptr;
	delete temp5;

	mark_cur = first_mark;
	fout.open(path);
	while(mark_cur){
		fout << mark_cur->totalMark << endl;
		mark_cur = mark_cur->next_Mark;
	}
	DeleteMarkList(first_mark);  delete initialMark;
	fout.close();*/
}

void StudentManagement(){
    int choice;
    while (true){
        clrscr(); //Heading();
        cout << "\n\n\t\t\t\t\t\t";
        for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " STUDENT MENU "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
        cout << "\n\n";
        cout << "\t\t\t\t\t\t1. Update student result\n\n";
        cout << "\t\t\t\t\t\t2. Go back\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

        fflush(stdin);
        cout << "\n\t\t\t\t\t\tEnter Your Choice : "; cin >> choice;
        switch (choice) {
            case 1: {
                clrscr(); //Heading();
                cout << "\n\n\t\t\t\t\t      ";
                for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " UPDATE RESULT "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                cout << "\n\n";
                string CourseID, StudentID;
                cout << "\t\t\t\t\t    Course ID           : ";
                cin >> CourseID;
                cout << "\n\t\t\t\t\t    Student ID          : ";
                cin >> StudentID;
                for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
                if (Find_Course(CourseID) && Find_ID(CourseID,StudentID)){
                    Mark* mark = getInitialMarkOfStudent(CourseID, StudentID);
                    clrscr(); //Heading();
                    cout << "\n\n\t\t\t\t\t\t ";
                    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
                    cout << "\n\n";
                    int based = 23; cout.precision(2);
                    gotoxy(15 + based, 12); cout << "Course ID";
                    gotoxy(15 + based, 14); cout << CourseID;
                    gotoxy(27 + based, 12); cout << "Total";
                    gotoxy(27 + based, 14); cout << mark->totalMark;
                    gotoxy(37 + based, 12); cout << "Final";
                    gotoxy(37 + based, 14); cout << mark->finalMark;
                    gotoxy(47 + based, 12); cout << "Midterm";
                    gotoxy(47 + based, 14); cout << mark->midtermMark;
                    gotoxy(57 + based, 12); cout << "Other";
                    gotoxy(57 + based, 14); cout << mark->otherMark;
                }
                else {
                    SetColor(12);
                    cout << "\n\t\t\t\t\t\t    Can not find";
                    SetColor(15);
                }
                _getch();
                Mark changeMark;

                cout << "\n\n\n\t\t\t\t\t\t Final mark: ";
                cin >> changeMark.finalMark;
                cout << "\n\t\t\t\t\t\t Midterm mark: ";
                cin >> changeMark.midtermMark;
                cout << "\n\t\t\t\t\t\t Other mark: ";
                cin >> changeMark.otherMark;

                changeMark = markAfterUpdate(changeMark);
                ChangeMarkFileAfterUpdate(changeMark,CourseID,StudentID);

                SetColor(10);
                cout << "\n\t\t\t\t\t      Changed successfully";
                SetColor(15);
                delay(1500);
                break;
            }
            case 2: return;
            default: SetColor(12); cout << "\n\t\t\t\t\t\t   Invalid choice"; SetColor(15); delay(1500);
        }
    }
}


