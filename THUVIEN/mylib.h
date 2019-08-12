#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h> 
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <iostream>
#include "Marcro.h"
#define EQUAL               0

using namespace std;
#define Enter 13
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;

const int UP =72+128;
const int DOWN =80+128;

const int F3=61+128;
const int F2=60+128;
const int F1=59+128;

const int ENTER =13;
const int ESC =27;
const int BACKSPACE = 8;

//char* Pwd () {
//     char S[40]; int i=0;
//     while ((S[i]= getch()) != Enter ) 
//     { printf ("%c", '*') ; i++ ; 
//     }
//     S[i]='\0';
//     return S;
//}
//
//int CheckPwd () {
//    int dem =0; 
//    for ( dem =1 ; dem <=3 ; dem++)
//    { printf( "Password :"); 
//      if (strcmp(Pwd(),PASSWORD) ==0)   return 1;
//      else printf ( "\nPassword sai. Hay nhap lai\n")  ; 
//    }
//    return 0;  
//}
string toUpper (string str){
    locale loc; 
    string n; 
    for (string::size_type i=0; i<str.length(); ++i)
        n += toupper(str[i], loc);
    return n;
}

void uppercaseChar (char *str){
    for(int i=0;i<strlen(str);i++){
        str[i] = toupper(str[i]);
    }
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

char *removeSpaces(char* s)
{
    char* cpy = s;  // an alias to iterate through s without moving s
    char* temp = s;

    while (*cpy)
    {
        if (*cpy != ' ')
            *temp++ = *cpy;
        cpy++;
    }
    *temp = 0;

     return s;
}


char* InputType(int n,int &endchar,int type){
	ShowCur(true);
	n+=1;
	int i =0;
	char *s = new char[n];
	char c ;
	while(1){
		c = getch();
		if(c==0 || c== 224)
		{
			c= getch();
			c+=128;
		}
		if(c==8 && i!=0){
			printf("\b \b"),i--;
		}
		if(c == ENTER || c == ESC){
			endchar = c; 
			break;
		}
		if(i>=n-1) continue;
		// 1: chu~ + so ; 2: only so; 3: onl chu
		if(type==1)
			if(!isalnum(c)) continue;
		if(type==2)
			if(!isdigit(c)) continue;
		if(type==3)
			if(!isalpha(c)) continue;
		if(type==4)
			if(!isdigit(c) || c < 48 || c > 50) continue;
		printf("%c",toupper(c));
		s[i++] = c;
		if(i==n)
			break;
	}
	s[i]='\0';
	return s;
}

///////////////////////////////////////////////

///////////////////////////////////////////////////
// 1800 <  NAM < 9999
const int MAX_NAM = 9999;
const int MIN_NAM = 1800;

struct NgayThang
{
	int ngay;
	int thang;
	int nam;
};
typedef struct NgayThang NGAY_THANG;

bool namNhuan(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int ngayHopLe(NGAY_THANG nt) {
	// return 0 chi ngay sai, 1 chi thang sai , 2 chi nam sai va 3 chi ngay gio dung format
	
	if (nt.nam > MAX_NAM || nt.nam < MIN_NAM)
		return 2;
	if (nt.thang < 1 || nt.thang > 12)
		return 1;
	if (nt.ngay < 1 || nt.ngay > 31)
		return 0;

	// xu ly thang 2 voi nam  nhuan
	if (nt.thang == 2)
	{
		if (namNhuan(nt.nam))
		{
			if (nt.ngay > 29)
				return 0;
		}
		else
		{
			if (nt.ngay > 28)
			{
				return 0;
			}
		}
	}
	if ((nt.thang == 4 || nt.thang == 6 || nt.thang == 9 || nt.thang == 11) && (nt.ngay > 30))
	{
		return 0;
	}
	return 3;
}

void xuatNgayThang(NGAY_THANG dt, int x, int y)
{
	gotoxy(x, y);
	cout << dt.ngay << " /";
	gotoxy(x + 4, y);
	cout << dt.thang << " /";
	gotoxy(x + 8, y);
	cout << dt.nam;
}

void LayNgayGioHT(NGAY_THANG &d)
{
	//    int ngay,thang,nam ;
	tm *today;
	time_t ltime;
	time(&ltime);
	
	 today = localtime( &ltime );
	
//	localtime_s(&today, &ltime);
	d.ngay = today->tm_mday;
	d.thang = today->tm_mon + 1;
	d.nam = today->tm_year + 1900;
}

int LayNamHT()
{
	tm *today;
	time_t ltime;
	time(&ltime);
	 today = localtime( &ltime );
//	localtime_s(&today, &ltime);
	return (today->tm_year + 1900);
}

int tinhNgay(NGAY_THANG dt)
{
	if (dt.thang < 3) {
		dt.nam--;
		dt.thang += 12;
	}
	return 365 * dt.nam + dt.nam / 4 - dt.nam / 10 + dt.nam / 400 + (153 * dt.thang - 457) / 5 + dt.ngay - 306;
}

int KhoangCachNgay(NGAY_THANG nt1)
{
	NGAY_THANG nt2;
	LayNgayGioHT(nt2);
	return ( tinhNgay(nt1) - tinhNgay(nt2));
}

int SoSanhNgay(NGAY_THANG nt1, NGAY_THANG nt2)
{
	return (tinhNgay(nt2) - tinhNgay(nt1));
}


int NhapNgayThang(NGAY_THANG &nt, int x, int y)
{	
	ShowCur(true);
	int flag = 2;

	LayNgayGioHT(nt);
	NGAY_THANG temp;
	temp.ngay = nt.ngay;
	temp.thang = nt.thang;
	temp.nam = nt.nam;

	xuatNgayThang(nt, x, y);
	
	while (true)
	{

		while (_kbhit())
		{
			int kb_hit = _getch();
			if (kb_hit >= 48 && kb_hit <= 57 )
			{
				if (flag == 0 )
				{
					
					int f = kb_hit - 48;
					temp.ngay = temp.ngay * 10 + (f);
					if (temp.ngay > 31)
					{
						temp.ngay /= 10;
						continue;
					}
					gotoxy(x, y);
					cout << temp.ngay;
					
				}
				else if (flag == 1)
				{
					
					int f = kb_hit - 48;
					temp.thang= temp.thang * 10 + (f);
					if (temp.thang > 12)
					{
						temp.thang /= 10;
						continue;
					}
					gotoxy(x + 4, y);
					cout << temp.thang;
				}
				else if (flag == 2)
				{
					
					int f = kb_hit - 48;
					temp.nam = temp.nam * 10 + (f);
					if (temp.nam > 9999)
					{
						temp.nam /= 10;
						continue;
					}
					gotoxy(x + 8, y);
					cout << temp.nam;
				}
				
			}
			
			else if (kb_hit == ENTER)
			{
				if (flag == 0)
				{

					gotoxy(x + 4, y);
					cout << temp.thang ;
					flag = 1;
				}
				else if (flag == 1)
				{

					gotoxy(x + 8, y);
					cout << temp.nam;
					flag = 2;
				}
				else if (flag == 2)
				{

					gotoxy(x  , y);
					cout << temp.ngay;
					flag = 0;
				}
			}
			else if (kb_hit == BACKSPACE && temp.ngay > 0 && temp.thang > 0 && temp.nam > 0)
			{
				cout << "\b" << " " << "\b";
				if (flag == 0 )
				{
					temp.ngay /= 10;
				}
				
				else if (flag == 1)
				{
					temp.thang /= 10;
				}
				else if (flag == 2)
				{
					temp.nam /= 10;
				}
			}
			else if (kb_hit == 0)
			{
				kb_hit = _getch();
				if (kb_hit == KEY_F10)
				{
				//	xuatNgayThang(temp,x+1,y);
					flag = ngayHopLe(temp);
					if (flag == 3)
					{
						// xoa dong thong bao
//						gotoxy(x - 17, y - 1);
//						cout << "                                                  ";
//						gotoxy(x, y);
//						cout << "                      ";
//						gotoxy(x + 1, y + 1);
//						cout << "            ";
//						gotoxy(x - 17, y - 2);
//						cout << "                                                  ";

						// kiem tra truong hop dac biet
						if (KhoangCachNgay(temp) < 0)
						{
						//	printf("khoang cach: %d", KhoangCachNgay(temp));
						//	xuatNgayThang(temp,x+50,y+1);
 
							return 1;
						}
						else
						{
							// chuyen du lieu ngay thang tam vao ngay thang chinh
//							printf("dung");
//							printf("khoang cach: %d", KhoangCachNgay(temp));
//							xuatNgayThang(temp,x+50,y+1);
							nt = temp;
							return 2;
						}		
					}
					else if (flag == 0)
					{
						gotoxy(x + 1, y + 1);
						cout << "Sai ngay!  ";
						gotoxy(x, y);
						cout << temp.ngay;
						continue;
					}
					else if (flag == 1)
					{
						gotoxy(x + 1, y + 1);
						cout << "Sai thang! ";
						gotoxy(x + 4, y);
						cout << temp.thang;
						continue;
					}
					else if (flag == 2)
					{
						gotoxy(x + 1, y + 1);
						cout << "Sai nam!   ";
						gotoxy(x + 8, y);
						cout << temp.ngay;
						continue;
					}
				
				}
			}
			else if (kb_hit == ESC)
			{

				// xoa dong thong bao
//				gotoxy(x - 17, y - 1);
//				cout << "                                                  ";
//				gotoxy(x, y);
//				cout << "                      ";
//				gotoxy(x - 17, y - 2);
//				cout << "                                                  ";
				return - 1;
			}
			
		}
	}
}
