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
        l.pHead= l.pTail= CreatNode(course);
    }
    else
    {
        Node* new_node = CreatNode(course);
        l.pTail->pNext = new_node;
        l.pTail = new_node;
    }
}
// Hàm hỏi người dùng để add course nào vào
void AddCourse(List& l)
{
    ifstream FileIn;
    FileIn.open("DATA/2021/1/course_list/courseList.txt", ios_base::in);
    int numbers_of_course = 0;
    while (!FileIn.eof())
    {
        string str;
        getline(FileIn,str);
        numbers_of_course++;
    }
    FileIn.close();
    FileIn.open("DATA/2021/1/course_list/courseList.txt", ios_base::in);
    Course* course = new Course[numbers_of_course];
    // đọc dữ liệu hàm từ file để in ra cho người dùng chọn
    for (int i = 0; i < numbers_of_course; i++)
    {
        getline(FileIn, course[i].CourseID);
    }
    FileIn.close();
    for (int i = 0; i < numbers_of_course; i++)
    {
        string strpath = "DATA/2021/1/course_list/" + course[i].CourseID+"/"+"info.txt";
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
        clrscr(); //Heading();
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
            gotoxy(109 + 1, 15 + i * 2); cout << course[i].SecondDayOfWeek << '-' <<course[i].SecondSessionOfWeek;
        }
        cout << "\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
        cout << "\n\t\t\t\t\t Input the course ID (0 to return): ";
        getline(cin,choice);
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

        bool Check1 = false; // check xem môn chọn co bi trùng giờ các môn trước hay không ?
        if (!Check)
        {
            for (int i = 0; i < numbers_of_course; ++i)
            {
                if (course[i].CourseID == choice)
                {
                    Node* node = l.pHead;
                    while (node)
                    {
                        if (course[i].FirstDayOfWeek == node->course.FirstDayOfWeek || course[i].SecondDayOfWeek == node->course.SecondDayOfWeek)
                        {
                            if(course[i].FirstSessionOfWeek == node->course.FirstSessionOfWeek || course[i].SecondSessionOfWeek == node->course.SecondSessionOfWeek)
                            Check1 = true;
                            break;
                        }
                        node = node->pNext;
                    }
                    if (!Check1)
                    {
                        SetColor(10);
                        cout << "\n\t\t\t\t\t\tAdd course successfully  " << endl;
                        SetColor(15);
                        delay(1500);
                        Add_Course(l, course[i]);
                        Check1 = true;
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
            if (!Check1){
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
void Read_My_Course_From_TXT(List& l)
{
    ifstream FileIn;
    FileIn.open("MyCourse.txt", ios_base::in);
    int numbers_of_course = 0;
    while (!FileIn.eof())
    {
        Course course;
        getline(FileIn, course.CourseID);
      //  cout << course.CourseID << " ";
        getline(FileIn, course.CourseName);
        getline(FileIn, course.TeacherName);
        FileIn >> course.NumberOfCredits;
        FileIn >> course.MaxNumOfStudent;
        FileIn.ignore(1);
        getline(FileIn,course.FirstDayOfWeek,' ');
        getline(FileIn,course.FirstSessionOfWeek,'\n');
        getline(FileIn,course.SecondDayOfWeek,' ');
        getline(FileIn,course.SecondSessionOfWeek,'\n');
        numbers_of_course++;
     //   cout << "1" << " ";
    }

    FileIn.close();
    FileIn.open("MyCourse.txt", ios_base::in);
    Course* course = new Course[numbers_of_course];
    for (int i = 0; i < numbers_of_course; i++)
    {
        getline(FileIn, course[i].CourseID);
        getline(FileIn, course[i].CourseName);
        getline(FileIn, course[i].TeacherName);
        FileIn >> course[i].NumberOfCredits;
        FileIn >> course[i].MaxNumOfStudent;
        FileIn.ignore(1);
        getline(FileIn,course[i].FirstDayOfWeek,' ');
        getline(FileIn,course[i].FirstSessionOfWeek,'\n');
        getline(FileIn,course[i].SecondDayOfWeek,' ');
        getline(FileIn,course[i].SecondSessionOfWeek,'\n');
    }

    InnitList(l);
    for (int i = 0; i < numbers_of_course; i++)
    {
        Add_Course(l, course[i]);
    }
    FileIn.close();
}
// Show thông tin về những course đã chọn
void Show_My_course(const List &l)
{
    clrscr();
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
        while (node)
        {
            gotoxy(2, 15 + i * 2); cout << i+ 1 << ". ";
            gotoxy(6 + 1, 15 + i * 2); cout << node->course.CourseID ;
            gotoxy(17 + 1, 15 + i * 2); cout << node->course.CourseName;
            gotoxy(54 + 1, 15 + i * 2); cout << node->course.TeacherName;
            gotoxy(77 + 1, 15 + i * 2); cout << node->course.NumberOfCredits ;
            gotoxy(89 + 1, 15 + i * 2); cout << node->course.MaxNumOfStudent ;
            gotoxy(99 + 1, 15 + i * 2); cout << node->course.FirstDayOfWeek << " " << node->course.FirstSessionOfWeek;
            gotoxy(109 + 1, 15 + i * 2); cout << node->course.SecondDayOfWeek << " " << node->course.SecondSessionOfWeek;
            i++;
            node = node->pNext;
        }
        cout << "\n\n";
        for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;
    }
}
// Hàm xoá course ra khỏi những gì đã chọn
void Remove_A_Course(List& l)
{
    clrscr();// Heading();
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
        Show_My_course(l);
        string name;
        cin.ignore();
        cout << "\n\n\t\t\t\t\t\t\  Course ID: ";
        getline(cin,name);
        for (int i = 0; i < name.length(); i++)
            name[i] = toupper(name[i]);
        Node* node = l.pHead;
        if (l.pHead->course.CourseID== name)
        {
            l.pHead = l.pHead->pNext;
            delete node;
        }
        else if (l.pTail->course.CourseID == name)
        {
            while (node->pNext != l.pTail)
            {
                node = node->pNext;
            }
            l.pTail = node;
            delete node->pNext;
            l.pTail->pNext = NULL;
        }
        else
        {
            while (node->pNext->course.CourseID != name)
            {
                node = node->pNext;
            }
            Node* node_del = node->pNext;
            node->pNext = node->pNext->pNext;
            delete node->pNext;
        }
        SetColor(10);
        cout << "\t\t\t\t\t  Removed Course Successfully" << endl;
        SetColor(15);
        delay(1500);
    }
}
// Hàm ghi course ra file
void Write_To_My_Course(const List &l)
{
    ofstream FileOut;
    FileOut.open("MyCourse.txt", ios_base::out);
    int count = 0;
    Node* node = l.pHead;
    while (node != NULL)
    {
        count ++;
        node = node->pNext;
    }
  //  FileOut << count << endl;
    node = l.pHead;
    while (node)
    {
        FileOut << node->course.CourseID << endl;
        FileOut << node->course.CourseName << endl;
        FileOut << node->course.TeacherName << endl;
        FileOut << node->course.NumberOfCredits << endl;
        FileOut << node->course.MaxNumOfStudent << endl;
        FileOut << node->course.FirstDayOfWeek << " " << node->course.FirstSessionOfWeek << endl;
        if (node->pNext == NULL) FileOut << node->course.SecondDayOfWeek<<" "<<node->course.SecondSessionOfWeek;
        else FileOut << node->course.SecondDayOfWeek<<" "<<node->course.SecondSessionOfWeek << endl;
        node = node->pNext;
    }
    FileOut.close();
}
void Menu(List& l)
{
    int choice;
    while (true)
    {
        clrscr(); //Heading();
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
        switch (choice){
            case 7:{
                SetColor(10);
                cout << "See you next time" << endl;
                delay(1500);
                SetColor(15);
                break;
            }
            case 1:{
                AddCourse(l);
                Write_To_My_Course(l);
                system("pause");
                break;
            }
            case 2:{
                Remove_A_Course(l);
                Write_To_My_Course(l);
                system("pause");
                break;
            }
            case 3:{
                Read_My_Course_From_TXT(l);
                Show_My_course(l);
                system("pause");
                break;
            }
            case 4:{
                My_Score(l);
                system("pause");
                break;
            }
            case 6:{
                Show_Profile();
                system("pause");
                break;
            }
        }
    }
}
// Hàm xem điểm từ file - Check tên người dùng
void My_Score(const List &l)
{
    ifstream FileIn;
    string pathfixed = "csvFile";
    clrscr(); //Heading();
    cout << "\n\n\t\t\t\t\t\t ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " Scoreboard "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    int based = 5; cout.precision(2);
    gotoxy(10 + based, 12); cout << "No";
    gotoxy(15 + based, 12); cout << "Course ID";
    gotoxy(27 + based, 12); cout << "Course name";
    gotoxy(67 + based, 12); cout << "Total";
    gotoxy(77 + based, 12); cout << "Final";
    gotoxy(87 + based, 12); cout << "Midterm";
    gotoxy(97 + based, 12); cout << "Other";
    
    int ID;
    cout << "Please input your ID = "; cin >> ID;

    int year;
    cout << "Input year = "; cin >> year;
    int semester;
    cout << "Input semester = "; cin >> semester;

    string str2;
    cin.ignore();
    cout << "Input course name = "; getline(cin, str2);

    string strpath = pathfixed + "/" + to_string(year) + "/" + to_string(semester) + "/" + str2 + ".csv";

    FileIn.open(strpath, ios_base::in);
    string str3;
    getline(FileIn, str3);
    cout << "---------------------" << endl;
    cout << str3 << endl;

    bool Check = false;
    while (FileIn.eof() == false)
    {
        int ID1 = 0;
        getline(FileIn, str3);
        string str4;
        for (int i = 0; i < str3.length(); i++)
        {
            if (str3[i] == ',')
            {
                int j = i + 1;
                while (str3[j] != ',')
                {
                    str4 += str3[j];
                    j += 1;
                }
                stringstream ss2;
                ss2 << str4;
                ss2 >> ID1;
                break;
            }
        }
        if (ID1 == ID)
        {
            Check = true;
            cout << str3 << endl;
            break;
        }

    }
    if (Check == false)
    {
        cout << "----------------------------" << endl;
        cout << "Can not find your information" << endl;
        cout << "----------------------------" << endl;
    }
    FileIn.close();
}
void Show_Profile()
{
    ifstream FileIn;
    int ID;
    cout << "Please input your ID = "; cin >> ID;
    int class1;
    cout << "Which class are you in ? "; cin >> class1;

    string strpath = "CLASS/21APCS" + to_string(class1) + "/" + to_string(ID) + ".txt";

    FileIn.open(strpath, ios_base::in);

    Student stu;
    FileIn >> stu.No;
    FileIn.ignore();
    getline(FileIn, stu.ID);
    getline(FileIn, stu.Name);
    getline(FileIn, stu.Gender);
    FileIn >> stu.Dob.day >> stu.Dob.month >> stu.Dob.year;
    FileIn.ignore();
    getline(FileIn, stu.socialID);
    FileIn.close();

    cout << "-----------------" << endl;
    cout << "Your information" << endl;
    cout << "No." << stu.No << endl;
    cout << "Your ID = " << stu.ID << endl;
    cout << "Your name = " << stu.Name << endl;
    cout << "Your gender = " << stu.Gender << endl;
    cout << "Your day of birth = " << stu.Dob.day << "-" << stu.Dob.month << "-" << stu.Dob.year << endl;
    cout << "Your social ID = " << stu.socialID << endl;
    cout << "-----------------" << endl;
    return;
}
