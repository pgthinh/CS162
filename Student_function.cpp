#include "Student.h"

void InnitList(List& l)
{
    l.pHead = l.pTail = NULL;
}
Node* CreatNode(Course course)
{
    Node* node = new Node;
    node->course = course;
    node->pNext = NULL;
    return node;
}
void Add_Course(List& l, const Course& course)
{
    if (l.pHead == NULL)
    {
        l.pHead = CreatNode(course);
    }
    else
    {
        Node* new_node = CreatNode(course);
        l.pTail->pNext = new_node;
        l.pTail = new_node;
    }
}
void AddCourse(List& l)
{
    ifstream FileIn;
    FileIn.open("Course_Co_San_De_Chon.txt", ios_base::in);
    int numbers_of_course;
    FileIn >> numbers_of_course;
    Course* course = new Course[numbers_of_course];
    for (int i = 0; i < numbers_of_course; i++)
    {
        FileIn >> course[i].ID;
        FileIn.ignore();
        getline(FileIn, course[i].name);
        getline(FileIn, course[i].Instructor);
        FileIn >> course[i].numbers_of_credits;
        FileIn >> course[i].maximum_students;
        FileIn.ignore();
        getline(FileIn, course[i].first_section);
        getline(FileIn, course[i].second_section);

    }
    FileIn.close();
    for (int i = 0; i < numbers_of_course; i++)
    {
        cout << i + 1 << endl;
        cout << "course ID = " << course[i].ID << endl;
        cout << "course name  = " << course[i].name << endl;
        cout << "course instructor = " << course[i].Instructor << endl;
        cout << "Numbers of credits = " << course[i].numbers_of_credits << endl;
        cout << "Maximum student = " << course[i].maximum_students << endl;
        cout << "first section = " << course[i].first_section << endl;
        cout << "second section = " << course[i].second_section << endl;
    }
    cout << "---------------------------" << endl;
    int choice;
    while (true)
    {
        cout << "Choose the course ID " << endl;
        cout << "If you dont want to choose any more , press 0 " << endl;
        cout << "Your choice = "; cin >> choice;
        if (choice == 0)
        {
            break;
        }
        for (int i = 0; i < numbers_of_course; i++)
        {
            if (course[i].ID == choice)
            {
                Add_Course(l, course[i]);
                break;
            }
        }
        cout << "Can not find any course with ID = " << choice << endl;
    }


}
void Read_My_Course_From_TXT(List& l)
{
    ifstream FileIn;
    FileIn.open("MyCourse.txt", ios_base::in);
    int numbers_of_course;
    FileIn >> numbers_of_course;
    Course* course = new Course[numbers_of_course];
    for (int i = 0; i < numbers_of_course; i++)
    {
        FileIn >> course[i].ID;
        FileIn.ignore();
        getline(FileIn, course[i].name);
        getline(FileIn, course[i].Instructor);
        FileIn >> course[i].numbers_of_credits;
        FileIn >> course[i].maximum_students;
        FileIn.ignore();
        getline(FileIn, course[i].first_section);
        getline(FileIn, course[i].second_section);
    }
    for (int i = 0; i < numbers_of_course; i++)
    {
        Add_Course(l, course[i]);
    }
    FileIn.close();
}
void Show_My_course(List l)
{
    ofstream FileOut;
    FileOut.open("MyCourse.txt", ios_base::out);
    if (l.pHead == NULL)
    {
        cout << "You have not registered any course" << endl;
    }
    else
    {
        Node* node = l.pHead;
        int count = 0;
        while (node != NULL)
        {
            cout << "Course ID = " << node->course.ID << endl;
            cout << "Course name = " << node->course.name << endl;
            cout << "Course Instructor = " << node->course.Instructor << endl;
            cout << "Numbers of credits = " << node->course.numbers_of_credits << endl;
            cout << "Maximum student = " << node->course.maximum_students << endl;
            cout << "first section = " << node->course.first_section << endl;
            cout << "second section = " << node->course.second_section << endl;
            count++;
            node = node->pNext;
        }
        node = l.pHead;
        FileOut << count << endl;
        while (node != NULL)
        {
            FileOut << node->course.ID << endl;
            FileOut << node->course.name << endl;
            FileOut << node->course.Instructor << endl;
            FileOut << node->course.numbers_of_credits << endl;
            FileOut << node->course.maximum_students << endl;
            FileOut << node->course.first_section << endl;
            FileOut << node->course.second_section << endl;
            node = node->pNext;
        }
        FileOut.close();
    }
}
void Remove_A_Course(List& l)
{
    if (l.pHead == NULL)
    {
        cout << "You dont have any course to remove" << endl;
    }
    else
    {
        int ID;
        cout << "Input course ID you want to remove = "; cin >> ID;
        Node* node = l.pHead;
        if (l.pHead->course.ID == ID)
        {
            l.pHead = l.pHead->pNext;
            delete node;
        }
        else
        {
            while (node->pNext->course.ID != ID)
            {
                node = node->pNext;
            }
            Node* node_del = node->pNext;
            node->pNext = node->pNext->pNext;
            delete node->pNext;
        }
    }
}
void Menu(List& l)
{
    int choice;
    while (true)
    {
        system("cls");
        cout << "STUDENT" << endl;
        cout << "1.Add course" << endl;
        cout << "2.Remove course" << endl;
        cout << "3.My courses" << endl;
        cout << "4.My scoreboard" << endl;
        cout << "5.Change password" << endl;
        cout << "6.Change profile" << endl;
        cout << "7.log out" << endl;
        cout << "------------------" << endl;
        cout << "Input your choice = "; cin >> choice;
        if (choice == 7)
        {
            cout << "See you next time" << endl;
            system("pause");
            break;
        }
        else if (choice == 1)
        {
            AddCourse(l);
            system("pause");
        }
        else if (choice == 2)
        {
            Remove_A_Course(l);
            system("pause");
        }
        else if (choice == 3)
        {
            Show_My_course(l);
            system("pause");
        }
    }
}
void getStudentScoreboard(int year,int term,string studentID,Course*& courseList,Mark*& mark){
    Mark* mark_cur = mark;
    Course* courseList_cur = courseList;
    string path = "DATA/" + to_string(year) + "/" + to_string(term) + "/students/" + studentID + "/marks.txt";
    ifstream fin(path);
    while(fin >> courseList_cur->CourseID >> mark_cur->totalMark >> mark_cur->finalMark >> mark_cur->midtermMark >> mark_cur->otherMark ){
        courseList_cur->next_Course = new Course;
        courseList_cur->next_Course->previous_Course = courseList_cur;
        courseList_cur = courseList_cur->next_Course;

        mark_cur->next_Mark = new Course;
        mark_cur->next_Mark->previous_Mark = mark_cur;
        mark_cur = mark_cur->next_Mark;
    }
    Course* temp1 = courseList_cur;
    courseList_cur = courseList_cur->previous_Course;
    courseList_cur->next_Course = nullptr;
    delete temp1;

    Course* temp2 = mark_cur;
    mark_cur = mark_cur->previouse_Mark;
    mark_cur->next_Mark = nullptr;
    delete temp2;
}
float getStudentGPA(string studentID,string className){
    string path = "CLASS/" + className + "/" + studentID + "_marks.txt";
    ifstream fin(path);
    float mark, sum = 0;
    int cnt = 0;
    while(fin >> mark){
        sum += mark;
        cnt += 1;
    }
    fin.close();
    float GPA = cnt > 0 ? sum / cnt : 0;
    return GPA / 10 * 4;
}