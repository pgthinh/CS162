#include <iostream>
#include "UpdateResult.h"
// 1. Tìm course
bool Find_Course(int year,int term, string CourseId)
{
	string courseName;
	string path = "DATA/" + to_string(year) + '/' + to_string(term) + "/course_list/courseList.txt";
	ifstream fin;  fin.open(path);
	while (fin >> courseName) {
		if (CourseId == courseName) {
			fin.close();  return true;
		}
	}
	fin.close();
	return false;
}
// 2. Tìm studentID trong course
bool Find_ID(int year,int term,string CourseID, string student_id)
{
	if (!Find_Course(year,term,CourseID)) return false;
	string id; string className;
	string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/course_list/" + CourseID + "/students.txt";
	ifstream fin(path);
	while (fin >> id >> className) {
		if (id == student_id) break;
	}
	fin.close();
	if (id == student_id) return true;
	return false;
}
// 3. 
Mark getInitialMarkOfStudent(int year,int term, string CourseID,string studentID){
	Mark score;
	Course courseList;
	string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + studentID + "/marks.txt";
	ifstream fin(path);
    while(fin >> courseList.CourseID >> score.totalMark >> score.finalMark >> score.midtermMark >> score.otherMark){
		if(courseList.CourseID == CourseID){
			break;
		}
	}
	fin.close();
	return score;
}
Mark markAfterUpdate(Mark& score){
	score.totalMark = score.finalMark / 10 * 5 + score.midtermMark / 10 * 3 + score.otherMark / 10 * 2;
	return score;
}
void ChangeMarkFileAfterUpdate(int year,int term,Mark& changeMark,string CourseID,string studentID){
	// change in year/semester/students/studentID/marks.txt
	Mark* first_mark = new Mark; Mark* mark_cur = first_mark;
	Course* first_course = new Course; Course* course_cur = first_course;
    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + studentID + "/marks.txt";
	ifstream fin; fin.open(path);
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
		if (course_cur->next_Course) {
			fout << course_cur->CourseID << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark << endl;
		}
		else {
			fout << course_cur->CourseID << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark;
		}
		course_cur = course_cur->next_Course;
		mark_cur = mark_cur->next_Mark;
	}
	DeleteCourseList(first_course);  DeleteMarkList(first_mark);
	fout.close();
	// change in year/semester/course_list/CourseID/marks.txt
	Student* first_student = new Student;  Student* student_cur = first_student;
	first_mark = new Mark;  mark_cur = first_mark;
	path = "DATA/" + to_string(year) + "/" + to_string(term) + "/course_list/" + CourseID + "/marks.txt";
    fin.open(path);
	while(fin >> student_cur->ID >> mark_cur->totalMark >> mark_cur->finalMark >> mark_cur->midtermMark >> mark_cur->otherMark){
		fin.ignore(); getline(fin, student_cur->Name, '\n');
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
		if (student_cur->next_Student) {
			fout << student_cur->ID  << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark << " " << student_cur->Name << endl;
		}
		else {
			fout << student_cur->ID << " " << mark_cur->totalMark << " " << mark_cur->finalMark << " " << mark_cur->midtermMark << " " << mark_cur->otherMark << " " << student_cur->Name;
		}
		student_cur = student_cur->next_Student;
		mark_cur = mark_cur->next_Mark;
	}
	DeleteStudentList(first_student);  DeleteMarkList(first_mark);
	fout.close();
}



