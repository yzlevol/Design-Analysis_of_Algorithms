#include "Maze.h"

/*	初始化  */
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); // 控制台句柄
int map[50][50] = { 0 };                         // 地图
POSITION Stack[2500] = { {0, 0} };               // 自定义数据结构-栈
QUEUE Queue[2500] = { {0, 0, 0} };               // 自定义数据结构-队列
int head = -1, tail = -1, top = -1;            // 队列头尾指针，栈指针

/*****************************************/
/*				 工具函数实现				 */
/*****************************************/
/**
 * brief: 更改光标的位置
 * \param line 行
 * \param col 列
 */
void SetPosition(int line, int col) // 更改光标的位置
{
    static COORD coord;
    coord.X = col * 2;
    coord.Y = line;
    SetConsoleCursorPosition(hout, coord);
}

/**
 * brief: 生成地图
 */
void MakeMap()
{
    int i, j, top = 0, ttt;
    POSITION s[2500] = { {0, 0} };
    POSITION sss[6] = { {0, 0} };
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
/**
 * brief: 输出迷宫
 */
void PrintMap()
{
    SetConsoleTextAttribute(hout, FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE |
        FOREGROUND_INTENSITY); // 墙的颜色
    SetPosition(0, 0);
    int i, j;
    for (i = 0; i <= MaxLine + 2; i++)
    {
        for (j = 0; j <= MaxColume + 2; j++)
        {
            cout << (map[i][j] == WALL ? WALLSTR : BLANKSTR);
        }
        if (i < MaxLine + 1)
            cout << endl;
    }

    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY); // 起点终点颜色
    // 设置迷宫进出口
    SetPosition(2, 1);
    cout << "Ｓ";
    SetPosition(MaxLine, MaxColume + 1);
    cout << "Ｅ";
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "                                                 " << endl;
    cout << "                                                 " << endl;
}
/**
 * brief : 改变控制台窗口大小
 * \param line 行
 * \param col 列
 */
void ChangeConsoleSize(int line, int col) // 改变控制台窗口大小
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
/**
 * brief : 清除所有搜索时留下的标记，只留下墙和路
 */
void ClearMap()
{
    int i, j;
    for (i = 0; i <= MaxLine + 2; i++)
        for (j = 0; j <= MaxColume + 2; j++)
            if (map[i][j] != WALL)
                map[i][j] = ROAD;
    map[2][1] = WALL;
    map[MaxLine][MaxColume + 1] = ROAD;
}
/**
 * brief : 设置光标是否可见  a=0不可见，a=1可见
 * \param a 参数
 */
void ChangeCursor(int a)
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, a };
    SetConsoleCursorInfo(hout, &cursor_info);
}

/*****************************************/
/*				 寻路算法实现				 */
/*****************************************/

/**
 * brief : 深度优先搜索
 * \param x 起点横坐标
 * \param y 起点纵坐标
 * \param dir 方向
 */
void DFS(int x, int y, int dir)
{
    memset(Stack, 0, sizeof(Stack));
    top = -1;
    int step = 0;
    while (top > -2 && (x != MaxLine || y != MaxColume + 1))
    {
        step++;
        top++;
        Stack[top].x = x;
        Stack[top].y = y;
        SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
            FOREGROUND_RED |
            FOREGROUND_INTENSITY); // 走过的路径颜色
        SetPosition(x, y);
        cout << RIGHTSTR;
        // Sleep(DELAY);
        if (map[x][y + 1] == ROAD)
        {
            map[x][y] = RIGHT;
            y++;
        }
        else
        {
            SetPosition(x, y);
            cout << DOWNSTR;
            // Sleep(DELAY);
            if (map[x + 1][y] == ROAD)
            {
                map[x][y] = DOWN;
                x++;
            }
            else
            {
                SetPosition(x, y);
                cout << LEFTSTR;
                // Sleep(DELAY/2);
                if (map[x][y - 1] == ROAD)
                {
                    map[x][y] = LEFT;
                    y--;
                }
                else
                {
                    SetPosition(x, y);
                    cout << UPSTR;
                    // Sleep(DELAY);
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
                        // Sleep(DELAY / 2);
                        top -= 2;
                        x = Stack[top + 1].x;
                        y = Stack[top + 1].y;
                    }
                }
            }
        }
        Sleep(DELAY / 2);//如果需要观察过程
        if (kbhit())
            if (getch() == '3')
                return;
    }
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // 路径颜色
    while (top >= 0)
    {
        SetPosition(Stack[top].x, Stack[top].y);
        cout << BLANKSTR;
        top--;
    }
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "扩展节点数：" << step << endl;
}
/**
 * brief : 广度优先搜索
 */
void BFS()
{
    int step = 0;
    int x, y, PreSub;
    tail = head = 0;
    memset(Queue, 0, sizeof(Queue));
    Queue[head].PreSub = -1;
    Queue[head].x = 2;
    Queue[head].y = 1;
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY); // 走过的路的颜色
    while (tail <= head)
    {
        x = Queue[tail].x;
        y = Queue[tail].y;
        PreSub = Queue[tail].PreSub;
        step++;//扩展节点数
        if (map[x - 1][y] == ROAD)
        {
            map[x - 1][y] = UP;
            SetPosition(x - 1, y);
            cout << UPSTR;
            head++;
            Queue[head].x = x - 1;
            Queue[head].y = y;
            Queue[head].PreSub = tail;
            if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
                break;
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
            if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
                break;
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
            if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
                break;
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
            if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
                break;
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
    SetConsoleTextAttribute(hout, 28); // 路径颜色
    if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
        while (tail != -1)
        {
            SetPosition(Queue[tail].x, Queue[tail].y);
            cout << BLANKSTR;
            tail = Queue[tail].PreSub;
        }
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY); // 起点终点颜色
    SetPosition(MaxLine, MaxColume + 1);
    cout << "Ｅ";
    SetPosition(2, 1);
    cout << "Ｓ";
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "扩展节点数：" << step << endl;
}

/**
 * brief : Dijkstra算法 非启发式搜索 找到终点就停止，若要找最短路径，将reachEnd改为false
 * */
void Dijkstra()
{
    int step = 0;
    bool reachEnd = false;
    // 用于记录每个节点的最佳路径距离
    int dist[MaxLine + 3][MaxColume + 4] = {};
    // 用于记录最短路径上每个节点的前驱节点
    POSITION prev[MaxLine + 3][MaxColume + 4] = {};
    // 走过的路的颜色
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);

    // 初始化距离和前驱节点
    for (int i = 0; i <= MaxLine + 2; ++i)
    {
        for (int j = 0; j <= MaxColume + 2; ++j)
        {
            dist[i][j] = INT_MAX;
            prev[i][j] = { -1, -1 };
        }
    }
    dist[2][1] = 0; // 起点(2, 1)到自身的距离为0

    // 定义一个集合来存储已经找到最短路径的节点
    bool settled[MaxLine + 3][MaxColume + 4] = {};

    // 将起点加入未确定集合
    std::vector<POSITION> unsettled;
    unsettled.push_back({ 2, 1 });

    while (!unsettled.empty())//当未确定集合不为空时
    {
        POSITION current = unsettled.back(); // 取得当前节点
        unsettled.pop_back();
        step++;
        // 标记当前节点为已确定
        settled[current.x][current.y] = true;

        // 检查四个方向的相邻节点
        for (int dir = RIGHT; dir <= UP; ++dir)
        {
            int newX = current.x, newY = current.y;
            switch (dir)
            {
            case RIGHT:
                ++newY;
                break;
            case DOWN:
                ++newX;
                break;
            case LEFT:
                --newY;
                break;
            case UP:
                --newX;
                break;
            }

            // 确保新的坐标在迷宫范围内且不是墙壁
            if (newX >= 0 && newX < MaxLine + 3 && newY >= 0 && newY < MaxColume + 4 &&
                map[newX][newY] != WALL && !settled[newX][newY])
            {
                int newDist = dist[current.x][current.y] + 1; // 计算新的距离
                // 如果找到了更短的路径，则更新距离和前驱节点
                if (newDist < dist[newX][newY])
                {
                    dist[newX][newY] = newDist;
                    prev[newX][newY] = current;
                    unsettled.push_back({ newX, newY });
                    SetPosition(newX, newY);
                    switch (dir)
                    {
                    case UP:
                        std::cout << UPSTR;
                        break;
                    case DOWN:
                        std::cout << DOWNSTR;
                        break;
                    case LEFT:
                        std::cout << LEFTSTR;
                        break;
                    case RIGHT:
                        std::cout << RIGHTSTR;
                        break;
                    }
                    Sleep(DELAY / 2);
                    // 如果到达终点，结束
                    if (newX == MaxLine && newY == MaxColume + 1)
                        reachEnd = false;
                }
            }
        }
        if (reachEnd)
            break;
    }

    // 打印最短路径
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // 路径颜色

    POSITION end = { MaxLine, MaxColume + 1 }; // 终点(M, N+1)
    if (dist[end.x][end.y] == INT_MAX)
    {
        std::cout << "No path found.\n";
        return;
    }

    // 从终点回溯到起点，打印最短路径
    std::vector<POSITION> path;
    POSITION at = end;
    while (at.x != 2 || at.y != 1)
    {
        path.push_back(at);
        at = prev[at.x][at.y];
    }
    path.push_back({ 2, 1 }); // 添加起点

    // 逆序打印找到的路径
    for (auto it = path.rbegin() + 1; it != path.rend() - 1; ++it)
    {
        SetPosition(it->x, it->y);
        // Sleep(DELAY/2);
        std::cout << BLANKSTR; // 使用蓝色色块标记路径
    }
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "扩展节点数：" << step << endl;
}

/**
 * brief : A*算法所需要的启发函数，使用曼哈顿距离
 */
 // 曼哈顿距离启发式函数
int Heuristic(const POSITION& p1, const POSITION& p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

/**
 * brief : A*算法
 */
void Astar()
{
    int step = 0;
    bool reachEnd = false;
    POSITION start = { 2, 2 };                 // 起点
    POSITION end = { MaxLine, MaxColume + 1 }; // 终点
	// 用于记录从起点到每个节点的距离
	std::vector<std::vector<int>> distToStart(MaxLine + 3, std::vector<int>(MaxColume + 4, INT_MAX));
	// 用于记录每个节点的前驱节点
    std::vector<std::vector<POSITION>> prev(MaxLine + 3, std::vector<POSITION>(MaxColume + 4, { -1, -1 }));
	// 用于记录每个节点的 F 值
    std::vector<std::vector<bool>> settled(MaxLine + 3, std::vector<bool>(MaxColume + 4, false));
	// 优先队列，按 F 值从小到大排序
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> pq;
    pq.push({ 0, start.x, start.y }); // 将起点的 F 值和坐标推入优先队列
    distToStart[start.x][start.y] = 0;
    // 走过的路的颜色
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);
	while (!pq.empty())//当未确定集合不为空时
    {
		int currentF, x, y;//当前节点的 F 值和坐标
		// 取出 F 值最小的节点
		std::tie(currentF, x, y) = pq.top();
        pq.pop();
        if (settled[x][y])
            continue;
		settled[x][y] = true;//标记当前节点为已确定

		if (x == end.x && y == end.y)//如果到达终点
        {
            reachEnd = true;
            break;
        }
		// 检查四个方向的相邻节点
        for (int dir = 0; dir < 4; ++dir)
        {
			// 定义方向数组，方便遍历四个方向
            int dx[4] = { 0, 1, 0, -1 };
            int dy[4] = { 1, 0, -1, 0 };
            int newX = x + dx[dir];
            int newY = y + dy[dir];
			// 确保新的坐标在迷宫范围内且不是墙壁
            if (newX >= 0 && newX < MaxLine + 1 && newY >= 1 && newY < MaxColume + 2 && map[newX][newY] != WALL)
            {
				// 计算新的距离和启发值
                int newDistToStart = distToStart[x][y] + 1;
                int newHeuristic = Heuristic({ newX, newY }, end);
                int newTotalCost = newDistToStart + newHeuristic;
				// 如果找到了更短的路径，则更新距离和前驱节点
                if (newTotalCost < distToStart[newX][newY])
                {
                    distToStart[newX][newY] = newTotalCost;
                    prev[newX][newY] = { x, y };
                    pq.push({ newTotalCost, newX, newY });
                    step++;
                    // 打印当前节点的探索方向
                    SetPosition(newX, newY);
                    switch (dir)
                    {
                    case 0:
                        std::cout << UPSTR;
                        break;
                    case 1:
                        std::cout << RIGHTSTR;
                        break;
                    case 2:
                        std::cout << DOWNSTR;
                        break;
                    case 3:
                        std::cout << LEFTSTR;
                        break;
                    }
                    Sleep(DELAY / 2); // 如果需要观察过程
                    if (newX == MaxLine && newY == MaxColume + 1)
                        reachEnd = true;
                }
            }
        }
        if (reachEnd)
            break;
    }

    if (!reachEnd || distToStart[end.x][end.y] == INT_MAX)
    {
        std::cout << "No path found." << std::endl;
        return;
    }

    // 回溯并打印最短路径
    ClearMap();
    PrintMap();
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hout, 28); // 路径颜色

    std::vector<POSITION> path;
    POSITION at = { MaxLine, MaxColume };
    while ((at.x > start.x || at.y > start.y))
    {
        path.push_back(at);
        at = prev[at.x][at.y];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    for (const POSITION& pos : path)
    {
        SetPosition(pos.x, pos.y);
        std::cout << BLANKSTR; // 使用"S"标记路径
    }

    SetConsoleTextAttribute(hout, 7); // 重置控制台文本属性
    SetPosition(MaxLine + 4, 0);
    std::cout << "扩展节点数: " << step << std::endl;
}

/**
 * brief : 动态规划算法
 */
void DPSearch() {
    int step = 0;
    // 用于记录从起点到每个节点的最短距离
    int dist[MaxLine + 3][MaxColume + 4] = { 0 };
    // 用于记录最短路径上每个节点的前驱节点
    POSITION prev[MaxLine + 3][MaxColume + 4];
    // 初始化最短距离数组，除了起点外，其他都设为 INT_MAX
    for (int i = 0; i <= MaxLine + 2; ++i) {
        for (int j = 0; j <= MaxColume + 3; ++j) {
            dist[i][j] = INT_MAX;
            prev[i][j].x = prev[i][j].y = -1; // 初始化 prev 数组
        }
    }
    dist[2][1] = 0; // 起点到自身的距离设为0

    std::queue<std::pair<int, int>> q;
    q.push({ 2, 1 });
    // 走过的路的颜色
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 如果已经到达终点，则停止搜索
        if (x == MaxLine && y == MaxColume) {
            break;
        }
        // 定义方向数组，方便遍历四个方向
        int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };//上下左右

        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];

            // 检查边界和是否是障碍物
            if (nx >= 0 && nx <= MaxLine && ny >= 0 && ny <= MaxColume + 1 && map[nx][ny] != WALL && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                prev[nx][ny].x = x;
                prev[nx][ny].y = y;
                q.push({ nx, ny });
                SetPosition(nx, ny);
                switch (i)
                {
                case 0:
                    std::cout << UPSTR;
                    break;
                case 1:
                    std::cout << DOWNSTR;
                    break;
                case 2:
                    std::cout << LEFTSTR;
                    break;
                case 3:
                    std::cout << RIGHTSTR;
                    break;
                }
                step++;
                Sleep(DELAY / 2); // 如果需要观察过程
            }
        }
    }

    // 打印最短路径
    ClearMap();
    PrintMap();
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hout, FOREGROUND_GREEN);

    POSITION end = { MaxLine, MaxColume };
    if (dist[end.x][end.y] == INT_MAX) {
        std::cout << "No path found." << std::endl;
        return;
    }

    // 回溯并打印最短路径
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // 路径颜色
    // 从终点回溯到起点，打印最短路径
    std::vector<POSITION> path;
    POSITION at = end;
    while (at.x > 2 || at.y > 1) {
        path.push_back(at);
        at = prev[at.x][at.y];
    }
    // 逆序打印找到的路径
    for (const POSITION& pos : path) {
        SetPosition(pos.x, pos.y);
        std::cout << BLANKSTR;
    }

    SetConsoleTextAttribute(hout, 7); // 重置控制台文本属性
    SetPosition(MaxLine + 4, 0);
    std::cout << "扩展节点数: " << step << std::endl;
}

