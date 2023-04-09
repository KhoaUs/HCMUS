#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <conio.h> // For keyboard input (getch())
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <cstring>
#include <string.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <io.h>    // Call _setmode
#include <fcntl.h>
#include <chrono>
#include <thread>


#define FOREGROUND_YELLOW 0x6
#define FOREGROUND_WHITE 0x7
#define FOREGROUND_GREY 0x8
#define FOREGROUND_LIGHTBLUE 0x9
#define BACKGROUND_BLACK 0x100
#define FOREGROUND_BLACK 0x00
using namespace std;

void changeColor(int color);

//Ham tinh kich thuoc man hinh console
void calculateColumnsConsole(int &columns, int &rows);

//Khoi tao gia tri bang
void setValueBoard (int **&Arr, int *&sub_arr, int size);

//Ham tro con tro van ban den vi tri co toa do x, y
void gotoXY(int x, int y);

bool matchShapeI(int cur_x, int cur_y, int old_x, int old_y, int **&a, int start_point, int size);


bool matchShapeL(int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int size);


bool matchShapeZ (int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int size);


void matchWholeShape(int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int &temp, int size);


void drawFrame (int pos_x, int pos_y, string str);

//Ham ve hinh chu nhat
void drawRec(int begin_x, int begin_y, int end_x, int end_y, char ch_1, char ch_2);

void highLightBlock(int x, int y, int **arr, int color, int start_point);

//Ve man hinh bat dau;
void drawMenu(int middle);

//Ham ve bang
void drawBoard (int Size, int start_point, int **a);

void operateBoard (int **&a, int cur_x, int cur_y, int old_x, int old_y, int size, int start_point, int x, int y);

//lam noi bat khung chon menu
void selectOption (int _x, int _y);

//thu hoi bo nho
void deleleDinamicArr(int **Arr, int size);

void selectLevel (int middle, int &size);

void drawLine(int **&Arr, int size, int start_point);

void play(int **&Arr, int *&sub_arr, int &size);

void Operating_System();