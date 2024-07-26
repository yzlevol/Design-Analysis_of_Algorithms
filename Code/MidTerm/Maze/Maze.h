#pragma once
#include <iostream>
#include <time.h>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <queue>
#include <tuple>
#include <functional>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)

/*****************************************/
/*				字符与常量定义				 */
/*****************************************/
#define WALLSTR   "█"
#define UPSTR     "↑"
#define DOWNSTR   "↓"
#define LEFTSTR   "←"
#define RIGHTSTR  "→"
//以上特殊符号是在手心输入法的特殊符号表里面找到的，因为不会写真的图形界面……（菜哭）
#define BLANKSTR  "  "//就是个全角的点
#define DEADSTR   "X"//全角的大写的英文字母x
#define DEAD        -1
#define DELAY       50
#define RIGHT       10
#define DOWN        20
#define LEFT        30
#define UP          40
#define ORIGINAL    0
#define WALL        1
#define ROAD        2

#define MaxLine 44
#define MaxColume 44
/*****************************************/
/*				  坐标定义				 */
/*****************************************/
struct POSITION {
	int x, y;	//坐标
	int G, H, F; //G当前开销，H预估开销，F总开销
    POSITION* Parent;//父节点
	//构造函数
    POSITION(int x = 0, int y = 0) : x(x), y(y), G(INT_MAX), H(0), F(0), Parent(nullptr) {}
};

struct ComparePosition {
    bool operator()(const POSITION& a, const POSITION& b) {
        return a.F > b.F; // Priority queue to get the lowest F cost node
    }
};

/*****************************************/
/*				  队列定义				 */
/*****************************************/
struct QUEUE
{
	int x, y;//坐标
	int PreSub;//前一个节点的下标
};

/*****************************************/
/*				 工具函数声明				 */
/*****************************************/
void SetPosition(int line, int col);//更改光标的位置
void MakeMap();	//生成地图
void PrintMap();	//打印地图
void ChangeConsoleSize(int line, int col);//更改控制台大小
void ClearMap();	//清空地图
void ChangeCursor(int a);//隐藏或显示光标

/*****************************************/
/*				 寻路算法声明				 */
/*****************************************/
void DFS(int x = 2, int y = 2, int dir = 0);//深度优先搜索
void BFS();//广度优先搜索
void Dijkstra();//Dijkstra算法
void Astar();//A*算法
void DPSearch();//动态规划算法
