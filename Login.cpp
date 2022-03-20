#include "Console.h"
#include "Login.h"
#include <iostream>
#include <string>
#include <fstream>
#include "supportfunction.h"
#include "Menu.h"
using namespace std;

void readPassword(string& password, int x, int y) {
	gotoxy(x, y); char character; string temp;
	while (character = _getch(), character != 13)
		if (character == '\b') {
			if (password.size() == 0) continue;
			gotoxy(x + (int)password.size()-1, y); cout << ' ';
			gotoxy(x + (int)password.size()-1, y);
			temp = password;
			password = "";
			for (int i = 0; i < temp.length()-1; i++) password += temp[i];
		}
		else {
			password += character;
			cout << "*";
		}
}

void getAccounts(User* &accounts){
    User* pCur = accounts;
	ifstream f;
	string s;

	f.open("Account_Data.txt");

	while (true){
	    User *temp = new User;
	    f >> s;
	    if (s == "0") break;
	    temp->id = s;
        f >> s; temp->username = s;
        f >> s; temp->password = s;
        f >> s; temp->role = s;
        if (pCur) pCur->Next = temp;
        else accounts = temp;
        pCur = temp;
        //cout << temp->id << " " << temp->username << " " << temp->role << endl;
    }
    f.close();
}

User login(string username, string password, User* accounts){
    User* pCur = accounts;
    while (pCur){
        if (username == pCur->username && password == pCur->password){
            User temp;
            temp.username = username;
            temp.password = password;
            temp.id = pCur->id;
            temp.role = pCur->role;
            return temp;
        }
        pCur = pCur->Next;
    }
    User temp;
    temp.password = "NONE"; temp.username = "NONE"; temp.role = "NONE";
    return temp;
}

void setCurrentAccount(User account){
    ofstream f;
    f.open("CurrentAccount.txt");
    f << account.id <<' ' << account.username << ' ' << account.password << ' ' << account.role;
    f.close();
}

void getCurrentAccount(User account){
    ifstream f;
    f.open("CurrentAccount.txt");
    f >> account.id >> account.username >> account.password >> account.role;
    f.close();
}

void Login(){
    clrscr();
    cout << "\n\n\n\n\n\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(219); cout << endl;
    cout << "\n";
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; cout << " " << char(220); for (int i = 1; i <= 8; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 4; i++)cout << char(220); for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << char(220); for (int i = 1; i <= 6; i++)cout << " "; cout << char(220); for (int i = 1; i <= 8; i++)cout << char(219); cout << "\t\t\t             COURSE MANAGEMENT SYSTEM";
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); cout << " "; cout << char(220); for (int i = 1; i <= 2; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << char(223); for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << char(223); for (int i = 1; i <= 2; i++)cout << char(219); cout << char(220); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219);
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; cout << char(219) << char(223) << " " << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " ";/**/cout << char(219) << char(223) << " ";
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); cout << "\t\t\t\t          VIETNAM NATIONAL UNIVERSITY";
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 4; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); cout << " " << char(223); for (int i = 1; i <= 11; i++)cout << char(219);
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; cout << char(219) << char(220) << " " << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); cout << "\t\t\t\t\t     HO CHI MINH CITY";
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 4; i++)cout << " "; cout << char(219) << char(219) << char(219) << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; cout << " " << char(220) << char(219); for (int i = 1; i <= 3; i++)cout << " ";/**/cout << char(219) << char(219) << char(219);
    cout << "\n\t"; for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 8; i++)cout << char(219); cout << char(223); for (int i = 1; i <= 3; i++)cout << " "; cout << char(223) << char(219); for (int i = 1; i <= 3; i++)cout << " "; for (int i = 1; i <= 3; i++)cout << char(219); for (int i = 1; i <= 3; i++)cout << " "; cout << char(219) << char(223); for (int i = 1; i <= 3; i++)cout << " "; cout << char(220); for (int i = 1; i <= 8; i++)cout << char(219); cout << char(223); cout << "\t\t\t\t\tUNIVERSITY OF SCIENCE";
    cout << "\n\n\n"; for (int rep = 1; rep <= 120; rep++) cout << char(219); cout << endl;
    cout << "\n\n\t\t\t\t\t\t";
    for (int rep = 1; rep <= 9; rep++) cout << char(219); cout << " LOGIN "; for (int rep = 1; rep <= 9; rep++) cout << char(219);
    cout << "\n\n\t\t\t\t\t\t"; cout << "Username : ";
    cout << "\n\n\t\t\t\t\t\t"; cout << "Password : ";

    fflush(stdin);
    string username;
    gotoxy(59, 25); cin >> username;
    string password;
    readPassword(password, 59, 27);

    User* accounts = NULL;
    getAccounts(accounts);

    User account = login(username, password, accounts);
    if (account.role == "NONE") {
        cout << "\n\n\t\t\t\t\t\tUnsuccessful login attempt";
        delay(1500);
        clrscr();
        Login();
    }else {
        setCurrentAccount(account);
        if (account.role == "Staff") staffMenu(); else studentMenu();
    }
}

void updateAccounts(User* &accounts){
    ofstream f;
    f.open("Account_Data.txt");
    accounts = accounts->Next;
    while (accounts != NULL){
        f << accounts->id << '\n' << accounts->username << '\n' << accounts->password << '\n' << accounts->role << '\n';
       // cout << accounts->id << '\n' << accounts->username << '\n' << accounts->password << '\n' << accounts->role << '\n';
        accounts = accounts->Next;
    }
    f << "0";
    f.close();
}
void changePassword(){
    clrscr(); Heading();
    cout << "\n\n\t\t\t\t\t       ";
    for (int rep = 1; rep <= 5; rep++) cout << char(219); cout << " CHANGE PASSWORD "; for (int rep = 1; rep <= 5; rep++) cout << char(219);
    cout << "\n\n";
    cout << "\t\t\t\t\t      Current password     : \n\n";
    cout << "\t\t\t\t\t      New password         : \n\n";
    cout << "\t\t\t\t\t      Confirm new password : \n\n";
    cout << "\t\t\t\t\t      Action(commit/back)  : \n\n\n\n";
    for (int rep = 1; rep <= 120; rep++) cout << char(220); cout << endl;

    string currentPassword, newPassword, confirmPassword;
    readPassword(currentPassword, 69, 12);
    readPassword(newPassword, 69, 14);
    readPassword(confirmPassword, 69, 16);


    User account;
    ifstream f;
    f.open("CurrentAccount.txt");
    f >> account.id >> account.username >> account.password >> account.role;
    f.close();

    do {
        string confirm; fflush(stdin);
        gotoxy(69, 18); cin >> confirm;
        if (confirm == "back") return; else
            if (confirm == "commit") {
                if (account.password != currentPassword){
                    gotoxy(46, 20); cout << "Current password is incorrect";
                    delay(1500); changePassword();
                    return;
                }

                if (newPassword != confirmPassword) {
                    gotoxy(46, 20); cout << "New password is incorrect";
                    delay(1500); changePassword();
                    return;
                }

                account.password = newPassword;
                setCurrentAccount(account);

                User* accounts = new User;
                getAccounts(accounts);
                User* pCur = accounts;

                while (pCur){
                    if (pCur->id == account.id){
                        pCur->password = account.password;
                        updateAccounts(accounts);
                        break;
                    }
                //    cout << pCur->id << '\n' << pCur->username << '\n' << pCur->password << '\n' << pCur->role << '\n';
                    pCur = pCur->Next;
                }

                cout << "\n\t\t\t\t\t   Password has been changed successfully";
                delay(1500); return;
            }
        gotoxy(69, 18); for (char c : confirm) cout << ' ';
    } while (true);
}
