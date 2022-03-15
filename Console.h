#ifndef Console_h
#define Console_h
#include <windows.h>
#include <conio.h>
#include <time.h>

void SetBGColor(WORD color);
void set_console_size();
void clrscr(void);
void gotoxy(short x,short y);
void SetColor(WORD color);
void delay(unsigned int mseconds);

#endif // Console_h
