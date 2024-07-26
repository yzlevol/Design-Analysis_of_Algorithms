#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <vector>
using namespace std;
#pragma warning(disable:4996) 

#define WALLSTR   "��"
#define UPSTR     "*"
#define DOWNSTR   "*"
#define LEFTSTR   "*"
#define RIGHTSTR  "*"
//����������������������뷨��������ű������ҵ��ģ���Ϊ����д���ͼ�ν��桭�����˿ޣ�
#define BLANKSTR  "  "//���Ǹ�ȫ�ǵĵ�
#define DEADSTR   "-"//ȫ�ǵĴ�д��Ӣ����ĸx
#define DEAD        -1
#define DELAY       50
#define UP          10
#define DOWN        20
#define LEFT        30
#define RIGHT       40
#define ORIGINAL    0
#define WALL        1
#define ROAD        2
//����������ǵ�ͼ
struct POSITION
{
	int x, y;
};

struct QUEUE
{
	int x, y;
	int PreSub;
};

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
int MaxLine = 38, MaxColume = 38;//�������޸����
int map[50][50] = { 0 };
POSITION Stack[2500] = { {0,0} };
QUEUE Queue[2500] = { {0,0,0} };
int head = -1, tail = -1, top = -1;

void SetPosition(int line, int col)//���Ĺ���λ��
{
	static COORD coord;
	coord.X = col * 2;
	coord.Y = line;
	SetConsoleCursorPosition(hout, coord);
}



void MakeMap()//������ͼ
{
	int i, j, top = 0, ttt;
	POSITION s[2500] = { {0,0} };
	POSITION sss[6] = { {0,0} };
	bool vis[50][50] = { false };

	memset(map, ORIGINAL, sizeof(map));
	for (i = 0; i <= MaxLine + 3; i++)
	{
		vis[i][0] = vis[i][MaxColume + 1] = vis[i][1] = vis[i][MaxColume + 2] = true;
		map[i][0] = map[i][MaxColume + 1] = map[i][1] = map[i][MaxColume + 2] = WALL;
	}
	for (i = 0; i <= MaxColume + 3; i++)
	{
		vis[0][i] = vis[MaxLine + 1][i] = vis[1][i] = vis[MaxLine + 2][i] = true;
		map[0][i] = map[MaxLine + 1][i] = map[1][i] = map[MaxLine + 2][i] = WALL;
	}
	map[2][1] = WALL;
	map[MaxLine][MaxColume + 1] = ROAD;
	s[0].x = s[0].y = 2;
	while (top >= 0)
	{
		vis[s[top].x][s[top].y] = true;
		map[s[top].x][s[top].y] = ROAD;
		for (i = s[top].x - 1; i <= s[top].x + 1; i++)
			for (j = s[top].y - 1; j <= s[top].y + 1; j++)
				if (map[i][j] == ORIGINAL)
				{
					vis[i][j] = true;
					map[i][j] = WALL;
				}
		i = s[top].x;
		j = s[top].y;
		if (!(vis[i - 2][j] && vis[i + 2][j] && vis[i][j - 2] && vis[i][j + 2]))
		{
			ttt = -1;
			if (!vis[i - 2][j])
			{
				ttt++;
				sss[ttt].x = i - 2;
				sss[ttt].y = j;
			}
			if (!vis[i + 2][j])
			{
				ttt++;
				sss[ttt].x = i + 2;
				sss[ttt].y = j;
			}
			if (!vis[i][j - 2])
			{
				ttt++;
				sss[ttt].x = i;
				sss[ttt].y = j - 2;
			}
			if (!vis[i][j + 2])
			{
				ttt++;
				sss[ttt].x = i;
				sss[ttt].y = j + 2;
			}
			ttt = rand() % (ttt + 1);

			top++;
			s[top].x = sss[ttt].x;
			s[top].y = sss[ttt].y;
			map[(i + s[top].x) / 2][(j + s[top].y) / 2] = ROAD;

		}
		else
		{
			top--;
		}
	}
}


void PrintMap()//����Թ�
{
	SetConsoleTextAttribute(hout, FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);   //ǽ����ɫ
	SetPosition(0, 0);
	int i, j;
	for (i = 0; i <= MaxLine + 2; i++)
	{
		for (j = 0; j <= MaxColume + 2; j++)
		{
			cout << (map[i][j] == WALL ? WALLSTR : BLANKSTR);
		}
		if (i < MaxLine + 1) cout << endl;
	}

	SetConsoleTextAttribute(hout, FOREGROUND_BLUE | 
                                   FOREGROUND_RED |
                                  FOREGROUND_INTENSITY);  //����յ���ɫ
	//�����Թ�������
	SetPosition(2, 1);
	cout << "��";
	SetPosition(MaxLine, MaxColume + 1);
	cout << "��";
	SetConsoleTextAttribute(hout, 7);
}

void ChangeConsoleSize(int line, int col)//�ı����̨���ڴ�С
{
	char LINE[10], COL[10], FINAL[50] = { '\0' };
	sprintf(LINE, "%d", line);
	sprintf(COL, "%d", col * 2);
	strcpy(FINAL, "mode con cols=");
	strcat(FINAL, COL);
	strcat(FINAL, " lines=");
	strcat(FINAL, LINE);
	system(FINAL);
}

void ClearMap()//�����������ʱ���µı�ǣ�ֻ����ǽ��·
{
	int i, j;
	for (i = 0; i <= MaxLine + 2; i++)
		for (j = 0; j <= MaxColume + 2; j++)
			if (map[i][j] != WALL)
				map[i][j] = ROAD;
	map[2][1] = WALL;
	map[MaxLine][MaxColume + 1] = ROAD;
}

void ChangeCursor(int a)  // ���ù���Ƿ�ɼ�  a=0���ɼ���a=1�ɼ� 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, a };
	SetConsoleCursorInfo(hout, &cursor_info);
}

void DFS(int x = 2, int y = 2, int dir = 0)
{
	memset(Stack, 0, sizeof(Stack));
	top = -1;
	while (top > -2 && (x != MaxLine || y != MaxColume + 1))
	{
		top++;
		Stack[top].x = x;
		Stack[top].y = y;
		SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
			                           FOREGROUND_RED |
			                      FOREGROUND_INTENSITY);    //�߹���·����ɫ
		SetPosition(x, y);
		cout << RIGHTSTR;
		Sleep(DELAY);
		if (map[x][y + 1] == ROAD)
		{
			map[x][y] = RIGHT;
			y++;
		}
		else
		{
			SetPosition(x, y);
			cout << DOWNSTR;
			Sleep(DELAY);
			if (map[x + 1][y] == ROAD)
			{
				map[x][y] = DOWN;
				x++;
			}
			else
			{
				SetPosition(x, y);
				cout << LEFTSTR;
				Sleep(DELAY);
				if (map[x][y - 1] == ROAD)
				{
					map[x][y] = LEFT;
					y--;
				}
				else
				{
					SetPosition(x, y);
					cout << UPSTR;
					Sleep(DELAY);
					if (map[x - 1][y] == ROAD)
					{
						map[x][y] = UP;
						x--;
					}

					else
					{
						map[x][y] = DEAD;
						SetPosition(x, y);
						cout << DEADSTR;
						Sleep(DELAY / 2);
						top -= 2;
						x = Stack[top + 1].x;
						y = Stack[top + 1].y;
					}
				}
			}
		}
		if (kbhit())
			if (getch() == '3')
				return;
	}
	ClearMap();
	PrintMap();
	SetConsoleTextAttribute(hout, 28); //·����ɫ
	while (top >= 0)
	{
		SetPosition(Stack[top].x, Stack[top].y);
		cout << BLANKSTR;
		top--;
	}
	SetConsoleTextAttribute(hout, 7);
}

void BFS()
{
	int x, y, PreSub;
	tail = head = 0;
	memset(Queue, 0, sizeof(Queue));
	Queue[head].PreSub = -1;
	Queue[head].x = 2;
	Queue[head].y = 1;
	SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
		                           FOREGROUND_RED |
		                     FOREGROUND_INTENSITY); //�߹���·����ɫ
	while (tail <= head)
	{
		x = Queue[tail].x;
		y = Queue[tail].y;
		PreSub = Queue[tail].PreSub;

		if (map[x - 1][y] == ROAD)
		{
			map[x - 1][y] = UP;
			SetPosition(x - 1, y);
			cout << UPSTR;
			head++;
			Queue[head].x = x - 1;
			Queue[head].y = y;
			Queue[head].PreSub = tail;
			if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1) break;
		}
		if (map[x + 1][y] == ROAD)
		{
			SetPosition(x + 1, y);
			cout << DOWNSTR;
			map[x + 1][y] = DOWN;
			head++;
			Queue[head].x = x + 1;
			Queue[head].y = y;
			Queue[head].PreSub = tail;
			if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1) break;
		}
		if (map[x][y + 1] == ROAD)
		{
			SetPosition(x, y + 1);
			cout << RIGHTSTR;
			map[x][y + 1] = RIGHT;
			head++;
			Queue[head].x = x;
			Queue[head].y = y + 1;
			Queue[head].PreSub = tail;
			if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1) break;
		}
		if (map[x][y - 1] == ROAD)
		{
			SetPosition(x, y - 1);
			cout << LEFTSTR;
			map[x][y - 1] = LEFT;
			head++;
			Queue[head].x = x;
			Queue[head].y = y - 1;
			Queue[head].PreSub = tail;
			if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1) break;
		}
		Sleep(DELAY / 2);
		tail++;
		if (kbhit())
			if (getch() == '3')
				return;
	}
	ClearMap();
	PrintMap();
	tail = Queue[head].PreSub;
	SetConsoleTextAttribute(hout, 28);  //·����ɫ
	if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
		while (tail != -1)
		{
			SetPosition(Queue[tail].x, Queue[tail].y);
			cout << BLANKSTR;
			tail = Queue[tail].PreSub;
		}
	SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
								   FOREGROUND_RED |
							  FOREGROUND_INTENSITY);   //����յ���ɫ
	SetPosition(MaxLine, MaxColume + 1);
	cout << "��";
	SetPosition(2, 1);
	cout << "��";
	SetConsoleTextAttribute(hout, 7);
}


int main()
{
	int i, j;
	ChangeConsoleSize(MaxLine + 3, MaxColume + 3);
	ChangeCursor(0);
	srand(time(0));
	MakeMap();
	PrintMap();
	//PrintMenu();
	while (1)
	{
		switch (getch())
		{
		case '1': //DFS
			ClearMap();
			PrintMap();
			DFS();
			fflush(stdin);
			break;
		case '2':  //BFS
			ClearMap();
			PrintMap();
			BFS();
			fflush(stdin);
			break;
		case '3':  //clear and replay
			ClearMap();
			PrintMap();
			break;
		case '4':  //refresh
			MakeMap();
			PrintMap();
			break;
		}
	}
	return 0;
}
