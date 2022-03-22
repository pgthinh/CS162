#include "SchoolYear.h"

#include <string>
using namespace std;

void createAndSetCurrentYear(int& year) {
    string path = "DATA/" + to_string(year);
    _mkdir(path.c_str());

    path = "csvFile/" + to_string(year);
    _mkdir(path.c_str());

    path = "DATA/cache/currentYear.txt";
    ofstream fout(path);
    fout << year;
    fout.close();
}
int getCurrentYear() {
    string path = "DATA/cache/currentYear.txt";
    ifstream fin(path);
    int year; fin >> year;
    fin.close();
    return year;
}