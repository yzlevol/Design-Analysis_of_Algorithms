#include "Maze.h"

/*	��ʼ��  */
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); // ����̨���
int map[50][50] = { 0 };                         // ��ͼ
POSITION Stack[2500] = { {0, 0} };               // �Զ������ݽṹ-ջ
QUEUE Queue[2500] = { {0, 0, 0} };               // �Զ������ݽṹ-����
int head = -1, tail = -1, top = -1;            // ����ͷβָ�룬ջָ��

/*****************************************/
/*				 ���ߺ���ʵ��				 */
/*****************************************/
/**
 * brief: ���Ĺ���λ��
 * \param line ��
 * \param col ��
 */
void SetPosition(int line, int col) // ���Ĺ���λ��
{
    static COORD coord;
    coord.X = col * 2;
    coord.Y = line;
    SetConsoleCursorPosition(hout, coord);
}

/**
 * brief: ���ɵ�ͼ
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
 * brief: ����Թ�
 */
void PrintMap()
{
    SetConsoleTextAttribute(hout, FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE |
        FOREGROUND_INTENSITY); // ǽ����ɫ
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
        FOREGROUND_INTENSITY); // ����յ���ɫ
    // �����Թ�������
    SetPosition(2, 1);
    cout << "��";
    SetPosition(MaxLine, MaxColume + 1);
    cout << "��";
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "                                                 " << endl;
    cout << "                                                 " << endl;
}
/**
 * brief : �ı����̨���ڴ�С
 * \param line ��
 * \param col ��
 */
void ChangeConsoleSize(int line, int col) // �ı����̨���ڴ�С
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
 * brief : �����������ʱ���µı�ǣ�ֻ����ǽ��·
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
 * brief : ���ù���Ƿ�ɼ�  a=0���ɼ���a=1�ɼ�
 * \param a ����
 */
void ChangeCursor(int a)
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, a };
    SetConsoleCursorInfo(hout, &cursor_info);
}

/*****************************************/
/*				 Ѱ·�㷨ʵ��				 */
/*****************************************/

/**
 * brief : �����������
 * \param x ��������
 * \param y ���������
 * \param dir ����
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
            FOREGROUND_INTENSITY); // �߹���·����ɫ
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
        Sleep(DELAY / 2);//�����Ҫ�۲����
        if (kbhit())
            if (getch() == '3')
                return;
    }
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // ·����ɫ
    while (top >= 0)
    {
        SetPosition(Stack[top].x, Stack[top].y);
        cout << BLANKSTR;
        top--;
    }
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "��չ�ڵ�����" << step << endl;
}
/**
 * brief : �����������
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
        FOREGROUND_INTENSITY); // �߹���·����ɫ
    while (tail <= head)
    {
        x = Queue[tail].x;
        y = Queue[tail].y;
        PreSub = Queue[tail].PreSub;
        step++;//��չ�ڵ���
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
    SetConsoleTextAttribute(hout, 28); // ·����ɫ
    if (Queue[head].x == MaxLine && Queue[head].y == MaxColume + 1)
        while (tail != -1)
        {
            SetPosition(Queue[tail].x, Queue[tail].y);
            cout << BLANKSTR;
            tail = Queue[tail].PreSub;
        }
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY); // ����յ���ɫ
    SetPosition(MaxLine, MaxColume + 1);
    cout << "��";
    SetPosition(2, 1);
    cout << "��";
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "��չ�ڵ�����" << step << endl;
}

/**
 * brief : Dijkstra�㷨 ������ʽ���� �ҵ��յ��ֹͣ����Ҫ�����·������reachEnd��Ϊfalse
 * */
void Dijkstra()
{
    int step = 0;
    bool reachEnd = false;
    // ���ڼ�¼ÿ���ڵ�����·������
    int dist[MaxLine + 3][MaxColume + 4] = {};
    // ���ڼ�¼���·����ÿ���ڵ��ǰ���ڵ�
    POSITION prev[MaxLine + 3][MaxColume + 4] = {};
    // �߹���·����ɫ
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);

    // ��ʼ�������ǰ���ڵ�
    for (int i = 0; i <= MaxLine + 2; ++i)
    {
        for (int j = 0; j <= MaxColume + 2; ++j)
        {
            dist[i][j] = INT_MAX;
            prev[i][j] = { -1, -1 };
        }
    }
    dist[2][1] = 0; // ���(2, 1)������ľ���Ϊ0

    // ����һ���������洢�Ѿ��ҵ����·���Ľڵ�
    bool settled[MaxLine + 3][MaxColume + 4] = {};

    // ��������δȷ������
    std::vector<POSITION> unsettled;
    unsettled.push_back({ 2, 1 });

    while (!unsettled.empty())//��δȷ�����ϲ�Ϊ��ʱ
    {
        POSITION current = unsettled.back(); // ȡ�õ�ǰ�ڵ�
        unsettled.pop_back();
        step++;
        // ��ǵ�ǰ�ڵ�Ϊ��ȷ��
        settled[current.x][current.y] = true;

        // ����ĸ���������ڽڵ�
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

            // ȷ���µ��������Թ���Χ���Ҳ���ǽ��
            if (newX >= 0 && newX < MaxLine + 3 && newY >= 0 && newY < MaxColume + 4 &&
                map[newX][newY] != WALL && !settled[newX][newY])
            {
                int newDist = dist[current.x][current.y] + 1; // �����µľ���
                // ����ҵ��˸��̵�·��������¾����ǰ���ڵ�
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
                    // ��������յ㣬����
                    if (newX == MaxLine && newY == MaxColume + 1)
                        reachEnd = false;
                }
            }
        }
        if (reachEnd)
            break;
    }

    // ��ӡ���·��
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // ·����ɫ

    POSITION end = { MaxLine, MaxColume + 1 }; // �յ�(M, N+1)
    if (dist[end.x][end.y] == INT_MAX)
    {
        std::cout << "No path found.\n";
        return;
    }

    // ���յ���ݵ���㣬��ӡ���·��
    std::vector<POSITION> path;
    POSITION at = end;
    while (at.x != 2 || at.y != 1)
    {
        path.push_back(at);
        at = prev[at.x][at.y];
    }
    path.push_back({ 2, 1 }); // ������

    // �����ӡ�ҵ���·��
    for (auto it = path.rbegin() + 1; it != path.rend() - 1; ++it)
    {
        SetPosition(it->x, it->y);
        // Sleep(DELAY/2);
        std::cout << BLANKSTR; // ʹ����ɫɫ����·��
    }
    SetConsoleTextAttribute(hout, 7);
    SetPosition(MaxLine + 4, 0);
    cout << "��չ�ڵ�����" << step << endl;
}

/**
 * brief : A*�㷨����Ҫ������������ʹ�������پ���
 */
 // �����پ�������ʽ����
int Heuristic(const POSITION& p1, const POSITION& p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

/**
 * brief : A*�㷨
 */
void Astar()
{
    int step = 0;
    bool reachEnd = false;
    POSITION start = { 2, 2 };                 // ���
    POSITION end = { MaxLine, MaxColume + 1 }; // �յ�
	// ���ڼ�¼����㵽ÿ���ڵ�ľ���
	std::vector<std::vector<int>> distToStart(MaxLine + 3, std::vector<int>(MaxColume + 4, INT_MAX));
	// ���ڼ�¼ÿ���ڵ��ǰ���ڵ�
    std::vector<std::vector<POSITION>> prev(MaxLine + 3, std::vector<POSITION>(MaxColume + 4, { -1, -1 }));
	// ���ڼ�¼ÿ���ڵ�� F ֵ
    std::vector<std::vector<bool>> settled(MaxLine + 3, std::vector<bool>(MaxColume + 4, false));
	// ���ȶ��У��� F ֵ��С��������
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> pq;
    pq.push({ 0, start.x, start.y }); // ������ F ֵ�������������ȶ���
    distToStart[start.x][start.y] = 0;
    // �߹���·����ɫ
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);
	while (!pq.empty())//��δȷ�����ϲ�Ϊ��ʱ
    {
		int currentF, x, y;//��ǰ�ڵ�� F ֵ������
		// ȡ�� F ֵ��С�Ľڵ�
		std::tie(currentF, x, y) = pq.top();
        pq.pop();
        if (settled[x][y])
            continue;
		settled[x][y] = true;//��ǵ�ǰ�ڵ�Ϊ��ȷ��

		if (x == end.x && y == end.y)//��������յ�
        {
            reachEnd = true;
            break;
        }
		// ����ĸ���������ڽڵ�
        for (int dir = 0; dir < 4; ++dir)
        {
			// ���巽�����飬��������ĸ�����
            int dx[4] = { 0, 1, 0, -1 };
            int dy[4] = { 1, 0, -1, 0 };
            int newX = x + dx[dir];
            int newY = y + dy[dir];
			// ȷ���µ��������Թ���Χ���Ҳ���ǽ��
            if (newX >= 0 && newX < MaxLine + 1 && newY >= 1 && newY < MaxColume + 2 && map[newX][newY] != WALL)
            {
				// �����µľ��������ֵ
                int newDistToStart = distToStart[x][y] + 1;
                int newHeuristic = Heuristic({ newX, newY }, end);
                int newTotalCost = newDistToStart + newHeuristic;
				// ����ҵ��˸��̵�·��������¾����ǰ���ڵ�
                if (newTotalCost < distToStart[newX][newY])
                {
                    distToStart[newX][newY] = newTotalCost;
                    prev[newX][newY] = { x, y };
                    pq.push({ newTotalCost, newX, newY });
                    step++;
                    // ��ӡ��ǰ�ڵ��̽������
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
                    Sleep(DELAY / 2); // �����Ҫ�۲����
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

    // ���ݲ���ӡ���·��
    ClearMap();
    PrintMap();
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hout, 28); // ·����ɫ

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
        std::cout << BLANKSTR; // ʹ��"S"���·��
    }

    SetConsoleTextAttribute(hout, 7); // ���ÿ���̨�ı�����
    SetPosition(MaxLine + 4, 0);
    std::cout << "��չ�ڵ���: " << step << std::endl;
}

/**
 * brief : ��̬�滮�㷨
 */
void DPSearch() {
    int step = 0;
    // ���ڼ�¼����㵽ÿ���ڵ����̾���
    int dist[MaxLine + 3][MaxColume + 4] = { 0 };
    // ���ڼ�¼���·����ÿ���ڵ��ǰ���ڵ�
    POSITION prev[MaxLine + 3][MaxColume + 4];
    // ��ʼ����̾������飬��������⣬��������Ϊ INT_MAX
    for (int i = 0; i <= MaxLine + 2; ++i) {
        for (int j = 0; j <= MaxColume + 3; ++j) {
            dist[i][j] = INT_MAX;
            prev[i][j].x = prev[i][j].y = -1; // ��ʼ�� prev ����
        }
    }
    dist[2][1] = 0; // ��㵽����ľ�����Ϊ0

    std::queue<std::pair<int, int>> q;
    q.push({ 2, 1 });
    // �߹���·����ɫ
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // ����Ѿ������յ㣬��ֹͣ����
        if (x == MaxLine && y == MaxColume) {
            break;
        }
        // ���巽�����飬��������ĸ�����
        int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };//��������

        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];

            // ���߽���Ƿ����ϰ���
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
                Sleep(DELAY / 2); // �����Ҫ�۲����
            }
        }
    }

    // ��ӡ���·��
    ClearMap();
    PrintMap();
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hout, FOREGROUND_GREEN);

    POSITION end = { MaxLine, MaxColume };
    if (dist[end.x][end.y] == INT_MAX) {
        std::cout << "No path found." << std::endl;
        return;
    }

    // ���ݲ���ӡ���·��
    ClearMap();
    PrintMap();
    SetConsoleTextAttribute(hout, 28); // ·����ɫ
    // ���յ���ݵ���㣬��ӡ���·��
    std::vector<POSITION> path;
    POSITION at = end;
    while (at.x > 2 || at.y > 1) {
        path.push_back(at);
        at = prev[at.x][at.y];
    }
    // �����ӡ�ҵ���·��
    for (const POSITION& pos : path) {
        SetPosition(pos.x, pos.y);
        std::cout << BLANKSTR;
    }

    SetConsoleTextAttribute(hout, 7); // ���ÿ���̨�ı�����
    SetPosition(MaxLine + 4, 0);
    std::cout << "��չ�ڵ���: " << step << std::endl;
}

