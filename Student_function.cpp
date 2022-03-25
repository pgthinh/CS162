﻿#include "Student.h"
// Hàm khởi tạo list ban đầu
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
    int numbers_of_course;
    FileIn >> numbers_of_course;
    Course* course = new Course[numbers_of_course];
    // đọc dữ liệu hàm từ file để in ra cho người dùng chọn
    FileIn.ignore();
    for (int i = 0; i < numbers_of_course; i++)
    {
        getline(FileIn, course[i].shortened_name);
    }
    FileIn.close();
    for (int i = 0; i < numbers_of_course; i++)
    {
        string strpath = "DATA/2021/1/course_list/" + course[i].shortened_name+"/"+"info.txt";
        FileIn.open(strpath, ios_base::in);
        getline(FileIn, course[i].shortened_name);
        getline(FileIn, course[i].name);
        getline(FileIn, course[i].Instructor);
        FileIn >> course[i].numbers_of_credits;
        FileIn >> course[i].maximum_students;
        FileIn.ignore();
        getline(FileIn, course[i].first_section);
        getline(FileIn, course[i].second_section);
        FileIn.close();
    }
    for (int i = 0; i < numbers_of_course; i++)
    {
        cout << i + 1 << endl;
        cout << "course ID = " << course[i].shortened_name << endl;
        cout << "course name  = " << course[i].name << endl;
        cout << "course instructor = " << course[i].Instructor << endl;
        cout << "Numbers of credits = " << course[i].numbers_of_credits << endl;
        cout << "Maximum student = " << course[i].maximum_students << endl;
        cout << "first section = " << course[i].first_section << endl;
        cout << "second section = " << course[i].second_section << endl;
    }
    cout << "---------------------------" << endl;
    cin.ignore();
    string choice;
    while (true)
    {
        cout << "Input the course ID " << endl;
        cout << "If you dont want to choose any more , press 0 " << endl;
        cout << "Your choice = "; getline(cin,choice);
        cout << "---------------------" << endl;
        for (int i = 0; i < choice.length(); i++)
        {
            choice[i] = toupper(choice[i]);
        }
        if (choice == "0")
        {
            break;
        }
        bool Check = false; // kiem tra xem course da chon hay chua ? neu chua chon thi duoc add 
        Node* node = l.pHead;
        while (node)
        {
            if (node->course.shortened_name == choice)
            {
                Check = true;
                break;
            }
            node = node->pNext;
        }
        if (!Check)
        {
            for (int i = 0; i < numbers_of_course; i++)
            {
                if (course[i].shortened_name == choice)
                {
                    Node* node = l.pHead;
                    bool Check1 = false; // check xem môn chọn co bi trùng giờ các môn trước hay không ?
                    while (node)
                    {
                        if (course[i].first_section == node->course.first_section || course[i].first_section == node->course.second_section || course[i].second_section == node->course.first_section || course[i].second_section == node->course.second_section)
                        {
                            Check1 = true;
                            break;
                        }
                        node = node->pNext;
                    }
                    if (!Check1)
                    {
                        cout << "----------------------------" << endl;
                        cout << "Add course successful" << endl;
                        cout << "----------------------------" << endl;
                        Add_Course(l, course[i]);
                        break;
                    }
                    else
                    {
                        cout << "----------------------------" << endl;
                        cout << "Bi trung h nen khong the them duoc nua" << endl;
                        cout << "----------------------------" << endl;
                        break;
                    }
                }
                else
                {
                    cout << "----------------------------" << endl;
                    cout << "Can not find any course with ID = " << choice << endl;
                    cout << "----------------------------" << endl;
                }
            }
        }
        else
        {
            cout << "----------------------------" << endl;
            cout << "You can not insert this course anymore" << endl;
            cout << "----------------------------" << endl;
        }
    }
}
// Đọc từ file xem đã chọn sẵn những hàm nào
void Read_My_Course_From_TXT(List& l)
{
    ifstream FileIn;
    FileIn.open("MyCourse.txt", ios_base::in);
    int numbers_of_course;
    FileIn >> numbers_of_course;
    FileIn.ignore();
    Course* course = new Course[numbers_of_course];
    for (int i = 0; i < numbers_of_course; i++)
    {
        getline(FileIn, course[i].shortened_name);
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
// Show thông tin về những course đã chọn
void Show_My_course(const List &l)
{
    if (!l.pHead)
    {
        cout << "----------------------------" << endl;
        cout << "You have not registered any course" << endl;
        cout << "----------------------------" << endl;
    }
    else
    {
        Node* node = l.pHead;
        int count = 0;
        while (node)
        {
            cout << "Course ID = " << node->course.shortened_name << endl;
            cout << "Course name = " << node->course.name << endl;
            cout << "Course Instructor = " << node->course.Instructor << endl;
            cout << "Numbers of credits = " << node->course.numbers_of_credits << endl;
            cout << "Maximum student = " << node->course.maximum_students << endl;
            cout << "first section = " << node->course.first_section << endl;
            cout << "second section = " << node->course.second_section << endl;
            cout << "----------------------------" << endl;
            count++;
            node = node->pNext;
        }
    }
}
// Hàm xoá course ra khỏi những gì đã chọn
void Remove_A_Course(List& l)
{
    if (!l.pHead)
    {
        cout << "----------------------------" << endl;
        cout << "You dont have any course to remove" << endl;
        cout << "----------------------------" << endl;
    }
    else
    {
        Show_My_course(l);
        string name;
        cin.ignore();
        cout << "Input course shortened name you want to remove = "; getline(cin,name);
        for (int i = 0; i < name.length(); i++)
        {
            name[i] = toupper(name[i]);
        }
        Node* node = l.pHead;
        if (l.pHead->course.shortened_name == name)
        {
            l.pHead = l.pHead->pNext;
            delete node;
        }
        else if (l.pTail->course.shortened_name == name)
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
            while (node->pNext->course.shortened_name != name)
            {
                node = node->pNext;
            }
            Node* node_del = node->pNext;
            node->pNext = node->pNext->pNext;
            delete node->pNext;
        }
        cout << "----------------------------" << endl;
        cout << "Removed Course Successfully" << endl;
        cout << "----------------------------" << endl;
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
    FileOut << count << endl;
    node = l.pHead;
    while (node)
    {
        FileOut << node->course.shortened_name << endl;
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
        cout << "5.Change password" << endl; // function này Thịnh làm
        cout << "6.View profile" << endl;
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
            Write_To_My_Course(l);
            system("pause");
        }
        else if (choice == 2)
        {
            Remove_A_Course(l);
            Write_To_My_Course(l);
            system("pause");
        }
        else if (choice == 3)
        {
            //Read_My_Course_From_TXT(l);
            Show_My_course(l);
            system("pause");
        }
        else if (choice == 4)
        {
            My_Score(l);
            system("pause");
        }
        else if (choice == 6)
        {
            Show_Profile();
            system("pause");
        }
    }
}
// Hàm xem điểm từ file - Check tên người dùng 
void My_Score(const List &l)
{
    ifstream FileIn;
    string pathfixed = "csvFile";
    int ID;
    cout << "Please input your ID = "; cin >> ID;

    int year;
    cout << "Input year = "; cin >> year;
    int semester;
    cout << "Input semester = "; cin >> semester;
    stringstream ss;
    stringstream ss1;

    ss << year;
    string str;
    ss >> str;
    string str1;
    ss1 << semester;
    ss1 >> str1;
    string str2;
    cin.ignore();
    cout << "Input semester name = "; getline(cin, str2);
    for (int i = 0; i < str2.length(); i++)
    {
        str2[i] = toupper(str2[i]);
    }
 
    string strpath = pathfixed + "/" + str + "/" + str + "_" + str1 + "/" +str2+"16"+str1+".csv";
    cout << strpath << endl;
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
    stringstream ss;
    ss << ID;
    string str; 
    ss >> str;
    int class1;
    cout << "Which class are you in ? "; cin >> class1;
    stringstream ss1;
    ss1 << class1;
    string str1;
    ss1 >> str1;

    string strpath = "CLASS/21APCS" + str1 + "/" + str + ".txt";

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
