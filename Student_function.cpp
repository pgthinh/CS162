#include "Student.h"
#include "Console.h"

void InnitList(List& l)
{
    l.pHead = l.pTail = NULL;
}
// Hàm tạo node
Node* CreatNode(Course course)
{
    Node* node = new Node;
    node->course = course;
    node->pNext = NULL;
    return node;
}
// Hàm add Course vào cuối linked list
void Add_Course(List& l, const Course& course)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = CreatNode(course);
    }
    else
    {
        Node* new_node = CreatNode(course);
        l.pTail->pNext = new_node;
        l.pTail = new_node;
    }
}
// Hàm hỏi người dùng để add course nào vào
void AddCourse(List& l, int year, int semester)
{
    ifstream FileIn;
    string path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/courseList.txt";
    FileIn.open(path, ios_base::in);
    int numbers_of_course = 0, number = 0;
    while (!FileIn.eof())
    {
        string str;
        getline(FileIn, str);
        numbers_of_course++;
    }
    FileIn.close();
    Node* node = l.pHead;
    while (node != NULL)
    {
        number++;
        node = node->pNext;
    }
    FileIn.open(path, ios_base::in);
    Course* course = new Course[numbers_of_course];
    // đọc dữ liệu hàm từ file để in ra cho người dùng chọn
    for (int i = 0; i < numbers_of_course; i++)
    {
        getline(FileIn, course[i].CourseID);
    }
    FileIn.close();
    for (int i = 0; i < numbers_of_course; i++)
    {
        string strpath = "DATA/" + to_string(year) + "/" + to_string(semester) + "/course_list/" + course[i].CourseID + "/" + "info.txt";
        FileIn.open(strpath, ios_base::in);
        getline(FileIn, course[i].CourseID);
        getline(FileIn, course[i].CourseName);
        getline(FileIn, course[i].TeacherName);
        FileIn >> course[i].NumberOfCredits;
        FileIn >> course[i].MaxNumOfStudent;
        FileIn.ignore();
        FileIn >> course[i].FirstDayOfWeek >> course[i].FirstSessionOfWeek;
        FileIn >> course[i].SecondDayOfWeek >> course[i].SecondSessionOfWeek;
        FileIn.close();
    }

    cin.ignore();
    string choice;
    while (true)
    {
        clrscr(); Heading();
        gotoxy(2, 12); cout << "No";
        gotoxy(6, 12); cout << " Course ID";
        gotoxy(6, 13); cout << " ";
        gotoxy(17, 12); cout << " Course name";
        gotoxy(17, 13); cout << " ";
        gotoxy(54, 12); cout << " Instructor";
        gotoxy(54, 13); cout << " ";
        gotoxy(77, 12); cout << " Number of";
        gotoxy(77, 13); cout << " credits";
        gotoxy(89, 12); cout << " Maximum";
        gotoxy(89, 13); cout << " student";
        gotoxy(99, 12); cout << " First";
        gotoxy(99, 13); cout << " session";
        gotoxy(109, 12); cout << " Second";
        gotoxy(109, 13); cout << " session";
        for (int i = 0; i < numbers_of_course; ++i) {
            gotoxy(2, 15 + i * 2); cout << i + 1 << ". ";
            gotoxy(6 + 1, 15 + i * 2); cout << course[i].CourseID;
            gotoxy(17 + 1, 15 + i * 2); cout << course[i].CourseName;
            gotoxy(54 + 1, 15 + i * 2); cout << course[i].TeacherName;
            gotoxy(77 + 1, 15 + i * 2); cout << course[i].NumberOfCredits;
            gotoxy(89 + 1, 15 + i * 2); cout << course[i].MaxNumOfStudent;
            gotoxy(99 + 1, 15 + i * 2); cout << course[i].FirstDayOfWeek << '-' << course[i].FirstSessionOfWeek;
            gotoxy(109 + 1, 15 + i * 2); cout << course[i].SecondDayOfWeek << '-' << course[i].SecondSessionOfWeek;
        }
        cout << "\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
        cout << "\n\t\t\t\t\t Input the course ID (0 to return): ";
        getline(cin, choice);
        for (int i = 0; i < choice.length(); i++)
            choice[i] = toupper(choice[i]);

        if (choice == "0") break;
        bool Check = false; // kiem tra xem course da chon hay chua ? neu chua chon thi duoc add
        Node* node = l.pHead;

        while (node)
        {
            if (node->course.CourseID == choice)
            {
                Check = true;
                break;
            }
            node = node->pNext;
        }
        bool Check2 = false;
        bool Check1 = false; // check xem môn chọn co bi trùng giờ các môn trước hay không ?
        if (!Check)
        {
            for (int i = 0; i < numbers_of_course; ++i)
            {
                if (course[i].CourseID == choice)
                {
                    Check2 = true;
                    Node* node = l.pHead;
                    while (node)
                    {
                        if (course[i].FirstDayOfWeek == node->course.FirstDayOfWeek && course[i].FirstSessionOfWeek == node->course.FirstSessionOfWeek)
                        {
                            Check1 = true;
                            break;
                        }
                        else if (course[i].SecondDayOfWeek == node->course.SecondDayOfWeek && course[i].SecondSessionOfWeek == node->course.SecondSessionOfWeek)
                        {
                            Check1 = true;
                            break;
                        }
                        node = node->pNext;
                    }
                    if (Check1 == false && number < 5)
                    {
                        SetColor(10);
                        cout << "\n\t\t\t\t\t\tAdd course successfully  " << endl;
                        SetColor(15);
                        delay(1500);
                        Add_Course(l, course[i]);
                        number++;
                        Check1 = true;
                        break;
                    }
                    else if (Check1 == false && number == 5)
                    {
                        SetColor(12);
                        cout << "\t\t\t\t You reached the maximum course" << endl;
                        SetColor(15);
                        delay(1500);
                        break;
                    }
                    else
                    {
                        SetColor(12);
                        cout << "\t\t\t\t You already have another the course at the same time" << endl;
                        SetColor(15);
                        delay(1500);
                        break;
                    }
                }
            }
            if (Check2 == false) {
                SetColor(12);
                cout << "\n\t\t\t\t\t Can not find any course with ID: " << choice;
                SetColor(15);
                delay(1500);
            }
        }
        else
        {
            SetColor(12);
            cout << "\n\t\t\t\t\t   You can not add this course anymore";
            SetColor(15);
            delay(1500);
        }
    }
}
// Đọc từ file xem đã chọn sẵn những hàm nào
void Read_My_Course_From_TXT(List& l, string& path, int& year, int& semester, string student_id)
{
    clrscr(); Heading();
    ifstream FileIn;
    cout << "\t\t\t\t\t\t   Input year = "; cin >> year;
    cout << "\t\t\t\t\t\t   Input semester = "; cin >> semester;

    path = "DATA/" + to_string(year) + "/" + to_string(semester) + "/students/" + student_id + "/" + "courses.txt";
    FileIn.open(path, ios_base::in);
    InnitList(l);
    while (FileIn.eof() != true)
    {
        Course* course = new Course[1];
        getline(FileIn, course[0].CourseID, '-');
        getline(FileIn, course[0].TeacherName, '-');
        string str;
        getline(FileIn, str, '-');
        for (int i = 0; i < 3; i++)
        {
            course[0].FirstDayOfWeek += str[i];
        }
        for (int i = 3; i < str.length(); i++)
        {
            course[0].FirstSessionOfWeek += str[i];
        }
        getline(FileIn, str);
        for (int i = 0; i < 3; i++)
        {
            course[0].SecondDayOfWeek += str[i];
        }
        for (int i = 3; i < str.length(); i++)
        {
            course[0].SecondSessionOfWeek += str[i];
        }
        Add_Course(l, course[0]);
    }
    FileIn.close();
    //system("pause");
}
// Show thông tin về những course đã chọn
void Show_My_course(const List& l)
{
    clrscr(); Heading();
    if (!l.pHead)
    {
        SetColor(12);
        cout << "\t\t\t\t\t   You have not registered any course";
        SetColor(15);
    }
    else
    {
        Node* node = l.pHead;
        int i = 0;
        gotoxy(2, 12); cout << "No";
        gotoxy(6, 12); cout << " Course ID";
        gotoxy(6, 13); cout << " ";

        gotoxy(17, 13); cout << " ";
        gotoxy(54, 12); cout << " Instructor";
        gotoxy(54, 13); cout << " ";

        gotoxy(99, 12); cout << " First";
        gotoxy(99, 13); cout << " session";
        gotoxy(109, 12); cout << " Second";
        gotoxy(109, 13); cout << " session";
        while (node)
        {
            gotoxy(2, 15 + i * 2); cout << i + 1 << ". ";
            gotoxy(6 + 1, 15 + i * 2); cout << node->course.CourseID;
            gotoxy(54 + 1, 15 + i * 2); cout << node->course.TeacherName;
            gotoxy(99 + 1, 15 + i * 2); cout << node->course.FirstDayOfWeek << " " << node->course.FirstSessionOfWeek;
            gotoxy(109 + 1, 15 + i * 2); cout << node->course.SecondDayOfWeek << " " << node->course.SecondSessionOfWeek;
            i++;
            node = node->pNext;
        }
        cout << "\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
    }
    _getch();
}
// Hàm xoá course ra khỏi những gì đã chọn
void Remove_A_Course(List& l)
{
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t       ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " REMOVE A COURSE "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    if (!l.pHead)
    {
        SetColor(12);
        cout << "\t\t\t\t\t   You dont have any course to remove";
        delay(1500);
        SetColor(15);
    }
    else
    {
        while (true)
        {
            system("cls");
            if (!l.pHead)
            {
                SetColor(12);
                cout << "\t\t\t\t\t   You dont have any course to remove";
                delay(1500);
                SetColor(15);
                break;
            }
            Show_My_course(l);
            string name;
            cin.ignore();
            cout << "\n\n\t\t\t\t\  Input Course ID that you want to remove ( 0 to return ) : ";
            getline(cin, name);
            if (name == "0")
            {
                break;
            }
            for (int i = 0; i < name.length(); i++)
                name[i] = toupper(name[i]);
            bool Check = false;
            if (l.pHead->course.CourseID == name)
            {
                Node* node = l.pHead;
                l.pHead = l.pHead->pNext;
                delete node;
                SetColor(10);
                cout << "\n\t\t\t\t\t     Removed Course Successfully" << endl;
                Check = true;
                SetColor(15);
                delay(1500);
            }
            else if (l.pTail->course.CourseID == name)
            {
                Node* node = l.pHead;
                while (node->pNext != l.pTail)
                {
                    node = node->pNext;
                }
                l.pTail = node;
                delete node->pNext;
                l.pTail->pNext = NULL;
                SetColor(10);
                cout << "\n\t\t\t\t\t     Removed Course Successfully" << endl;
                Check = true;
                SetColor(15);
                delay(1500);
            }
            else
            {
                Node* node = l.pHead;
                while (node->pNext != NULL)
                {
                    if (node->pNext->course.CourseID == name)
                    {
                        /*Node* node_del = node->pNext;*/
                        node->pNext = node->pNext->pNext;
                        SetColor(10);
                        cout << "\n\t\t\t\t\t     Removed Course Successfully" << endl;
                        Check = true;
                        //delete node_del;
                        SetColor(15);
                        delay(1500);
                        break;
                    }
                    node = node->pNext;
                }
            }
            if (Check == false)
            {
                cout << "Can not find the course you want to remove " << endl;
                delay(1500);
            }

        }
    }
}
// Hàm ghi course ra file
void Write_To_My_Course(const List& l, string path)
{
    ofstream FileOut;
    FileOut.open(path, ios_base::out);
    Node* node = l.pHead;
    while (node)
    {
        if (node->pNext != NULL)
        {
            FileOut << node->course.CourseID << "-";
            FileOut << node->course.TeacherName << "-";
            FileOut << node->course.FirstDayOfWeek << node->course.FirstSessionOfWeek << "-";
            FileOut << node->course.SecondDayOfWeek << node->course.SecondSessionOfWeek << endl;
        }
        else
        {
            FileOut << node->course.CourseID << "-";
            FileOut << node->course.TeacherName << "-";
            FileOut << node->course.FirstDayOfWeek << node->course.FirstSessionOfWeek << "-";
            FileOut << node->course.SecondDayOfWeek << node->course.SecondSessionOfWeek;
        }
        node = node->pNext;
    }
    FileOut.close();
}
void Menu(List& l, string& path, int year, int semester, string ID)
{
    int choice;
    while (true)
    {
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

        cout << "\t\t\t\t\t\t Selection: "; cin >> choice;
        switch (choice) {
        case 7: {
            deleteList(l);
            SetColor(10);
            cout << "\t\t\t\t\t\t See you next time" << endl;
            delay(1500);
            SetColor(15);
            Login();
            break;
        }
        case 1: {
            AddCourse(l, year, semester);
            Write_To_My_Course(l, path);
            break;
        }
        case 2: {
            Remove_A_Course(l);
            Write_To_My_Course(l, path);
            break;
        }
        case 3: {
            Show_My_course(l);
            break;
        }
        case 4: {
            My_Score(l, ID, year, semester);
            break;
        }
        case 6: {
            Show_Profile(ID);
            break;
        }
        case 5: {
            changePassword();
            break;
        }
        default: {
            SetColor(10);
            cout << "\n\t\t\t\t\t\t Please input the right command" << endl;
            delay(1500);
            SetColor(15);
        }
        }
    }
}
// Hàm xem điểm từ file - Check tên người dùng
void My_Score(const List& l, string ID, int year, int semester)
{
    if (l.pHead == NULL)
    {
        SetColor(12);
        cout << "\t\t\t\t\t     You have not registered any course yet" << endl;
        SetColor(15);
        delay(1500);
        return;
    }

    ifstream FileIn;
    string pathfixed = "DATA/" + to_string(year) + "/" + to_string(semester) + "/students/" + ID + "/" + "marks.txt";
    FileIn.open(pathfixed, ios::in);
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t\t ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    int based = 5; cout.precision(2);
    gotoxy(30 + based, 12); cout << "No";
    gotoxy(35 + based, 12); cout << "Course ID";
    gotoxy(47 + based, 12); cout << "Total";
    gotoxy(57 + based, 12); cout << "Final";
    gotoxy(67 + based, 12); cout << "Midterm";
    gotoxy(77 + based, 12); cout << "Other";
    cout << endl;
    Node* node = l.pHead;
    int ncourse = 0;
    while (FileIn.eof() != true)
    {
        string str1;
        getline(FileIn, str1);
        ncourse++;
    }
    FileIn.close();

    int a = 13; int no = 1;
    FileIn.open(pathfixed, ios::in);
    for (int i = 0; i < ncourse; i++)
    {
        string str1, total, final, midterm, other, string_course_name;
        getline(FileIn, str1);
        int j = 0;
        while (str1[j] != ' ')
        {
            string_course_name += str1[j];
            j++;
        }
        Node* node = l.pHead;
        bool Check = false;
        while (node != NULL)
        {
            if (string_course_name == node->course.CourseID)
            {
                Check = true;
            }
            node = node->pNext;
        }
        if (Check == true)
        {
            gotoxy(30 + based, a); cout << no;
            Mark* mark = new Mark;
            gotoxy(35 + based, a); cout << string_course_name << " ";
            j++;

            while (str1[j] != ' ')
            {
                total += str1[j];
                j++;
            }
            cout << str1[j];
            j++;
            stringstream ss;
            ss << total;
            ss >> mark->totalMark;
            gotoxy(47 + based, a); cout << mark->totalMark << " ";

            while (str1[j] != ' ')
            {
                final += str1[j];
                j++;
            }
            cout << str1[j];
            j++;
            stringstream ss1;
            ss1 << final;
            ss1 >> mark->finalMark;
            gotoxy(57 + based, a); cout << mark->finalMark << " ";

            while (str1[j] != ' ')
            {
                midterm += str1[j];
                j++;
            }
            cout << str1[j];
            j++;
            stringstream ss2;
            ss2 << midterm;
            ss2 >> mark->midtermMark;
            gotoxy(67 + based, a); cout << mark->midtermMark << " ";

            for (int k = j; k < str1.length(); k++)
            {
                other += str1[k];
            }
            stringstream ss3;
            ss3 << other;
            ss3 >> mark->otherMark;
            gotoxy(77 + based, a); cout << mark->otherMark << endl;
            a++; no++;
        }

    }
    FileIn.close();
    _getch();
}

void Show_Profile(string ID)
{
    ifstream FileIn;
    string class1;
    cout << "\n\t\t\t\t\t\t Which class are you in ? "; cin >> class1;


    string strpath = "CLASS/" + class1 + "/" + ID + ".txt";

    FileIn.open(strpath, ios::in);
    Student stu;
    FileIn >> stu.No;
    FileIn.ignore();
    getline(FileIn, stu.ID, '\n');
    getline(FileIn, stu.Name, '\n');
    getline(FileIn, stu.Gender, '\n');
    FileIn >> stu.Dob.day >> stu.Dob.month >> stu.Dob.year;
    FileIn.ignore();
    getline(FileIn, stu.socialID, '\n');
    FileIn.close();

    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t\t   ";

    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " " << stu.Name << " "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";

    gotoxy(50, 10 + 2); cout << "Student ID: " << stu.ID;
    gotoxy(50, 10 + 4); cout << "Full name: " << stu.Name;
    gotoxy(50, 10 + 6); cout << "Gender: " << stu.Gender;
    gotoxy(50, 10 + 8); cout << "Date of Birth: " << stu.Dob.day << "-" << stu.Dob.month << "-" << stu.Dob.year;
    gotoxy(50, 10 + 10); cout << "Social ID: " << stu.socialID;

    cout << "\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    _getch();
}
void deleteList(List& l) {
    if (!l.pHead) return;
    Node* cur;
    while (l.pHead) {
        cur = l.pHead;
        l.pHead = l.pHead->pNext;
        delete cur;
    }
}