#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<random>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<set>
#include<cctype>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define JADE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_JADE 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHTER_WHITE 15
#define ARROW_FIRST 224
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

using namespace std;
using v2d=vector<vector<int>>;
using v2b=vector<vector<bool>>;
using vpii=vector<pair<int,int>>;

HANDLE g_HndOut=GetStdHandle(STD_OUTPUT_HANDLE),g_HndIn=GetStdHandle(STD_INPUT_HANDLE);

namespace DF{
    void ClearConsoleScreen();
    void SetColor(int,int);
    void HideConsoleCursor();
    void GotoXY(int,int);
    void GotoXY(COORD);
};
inline int rnd2o4();
template<typename _2DVec> int InitVec(_2DVec,size_t,size_t);
bool IsV2dFull(v2d);
int GetDir();
bool IsntGameOver(v2d);
void MoveS(v2d&);
void MoveW(v2d&);
void MoveA(v2d&);
void MoveD(v2d&);
void UpdateScreen(v2d);
void RandNumGen(v2d&);
void PrintStartScreen();
void GameMenu();
void StartGame();
