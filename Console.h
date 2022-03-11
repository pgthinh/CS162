#ifndef Console_h
#define Console_h
#include <windows.h>
#include <conio.h>

void SetBGColor(WORD color);
void clrscr(void);
void gotoxy(short x,short y);
void SetColor(WORD color);

#endif // Console_h
