#pragma once
#include"Maze.h"
#include<ctime>
clock_t start, finish;
/*	引用外部声明 */
extern HANDLE hout;
extern int map[50][50];
extern POSITION Stack;//栈的实现
extern QUEUE Queue;
extern int head;//队列头
extern int tail;//队列尾
extern int top;//栈顶


int main()
{
	ChangeConsoleSize(MaxLine + 7, MaxColume + 4);
	ChangeCursor(0);
	srand(time(0));
	MakeMap();
	PrintMap();
	while (1)
	{
		switch (getch())
		{
		case '0':
			exit(0);
			break;
		case '1': //DFS
			ClearMap();
			PrintMap();
			SetPosition(MaxLine + 3, 0);
			cout << "|-*-*-*-*--*-*-====== DFS算法寻路展示 ======-*-*-*-*-*-*-|" << endl;
			start = clock();
			DFS();
			finish = clock();
			SetPosition(MaxLine + 5, 0);
			cout << "DFS算法寻路展示用时：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
			fflush(stdin);
			break;
		case '2':  //BFS
			ClearMap();
			PrintMap();
			SetPosition(MaxLine + 3, 0);
			cout << "|-*-*-*-*--*-*-====== BFS算法寻路展示 ======-*-*-*-*-*-*-|" << endl;
			start = clock();
			BFS();
			finish = clock();
			SetPosition(MaxLine + 5, 0);
			cout << "BFS算法寻路展示用时：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
			fflush(stdin);
			break;
		case '3':  //Dijkstra
			ClearMap();
			PrintMap();
			SetPosition(MaxLine + 3, 0);
			cout << "|-*-*-*-*--*-*-=== Dijkstra算法寻路展示 ===-*-*-*-*-*-*-|" << endl;
			start = clock();
			Dijkstra();
			finish = clock();
			SetPosition(MaxLine + 5, 0);
			cout << "Dijkstra算法寻路展示用时：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
			fflush(stdin);
			break;
		case '4':  //A-star
			ClearMap();
			PrintMap();
			SetPosition(MaxLine + 3, 0);
			cout << "|-*-*-*-*--*-*-===  A-star算法寻路展示  ===-*-*-*-*-*-*-|" << endl;
			start = clock();
			Astar();
			finish = clock();
			SetPosition(MaxLine + 5, 0);
			cout << "A-star算法寻路展示用时：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
			fflush(stdin);
			break;
		case '5':
			ClearMap();
			PrintMap();
			SetPosition(MaxLine + 3, 0);
			cout << "|-*-*-*-*--*-*-===  动态规划算法寻路展示  ===-*-*-*-*-*-*-|" << endl;
			start = clock();
			DPSearch();
			finish = clock();
			SetPosition(MaxLine + 5, 0);
			cout << "动态规划算法寻路展示用时：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
			fflush(stdin);
			break;
		case '6':  //clear and replay
			ClearMap();
			PrintMap();
			break;
		case '7':  //refresh
			MakeMap();
			PrintMap();
			break;
		}
	}
	return 0;
}