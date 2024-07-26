/**
 * @file 5-3.cpp
 * @brief 机器设计问题的回溯法解法
 * @version 0.1
 * @date 2024-05-06
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 100;

struct State
{
    int weight = 0; // 当前机器的总重量
    int cost = 0;   // 当前机器的总价格
};

vector<vector<int>> cost(MAXN, vector<int>(MAXN)), weight(MAXN, vector<int>(MAXN)); // 部件的价格和重量
vector<int> minSum(MAXN), result(MAXN), tempResult(MAXN);                           // 最小重量和结果
int m, n, d, minWeight = INT_MAX;                                                   // 供应商数量，部件数量，总价格限制，最小重量
State currentState;                                                                 // 当前状态

/**
 * @brief 输入数据
 */
void input()
{
    cin >> n >> m >> d;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> cost[i][j];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> weight[i][j];
        }
    }
}

/**
 * @brief 设置最小重量数组
 */
void setMinSum()
{
    minSum[n + 1] = 0;
    for (int i = n; i >= 1; --i)
    {
        int minWeight = *min_element(weight[i].begin() + 1, weight[i].begin() + 1 + m);
        minSum[i] = minSum[i + 1] + minWeight;
    }
}

/**
 * @brief 回溯函数
 * @param p 当前部件的索引
 */
void backtrack(int p)
{
    if (p == 1)
        setMinSum();
    if (p > n) // 判断是否到达叶子节点
    {
        if (currentState.weight < minWeight) // 更新最小重量
        {
            minWeight = currentState.weight;
            copy(tempResult.begin() + 1, tempResult.begin() + 1 + n, result.begin() + 1);
        }
        return;
    }
    // 该叶子结点添加后比最小重量小，剪枝
    if (minSum[p] + currentState.weight > minWeight)
    {
        return;
    }
    for (int i = 1; i <= m; ++i) // 遍历所有供应商
    {
        // 该供应商的价格小于总价格限制
        if (currentState.cost + cost[p][i] <= d)
        {
            currentState.weight += weight[p][i];
            currentState.cost += cost[p][i];
            tempResult[p] = i;                   // 记录结果
            backtrack(p + 1);                    // 继续
            currentState.weight -= weight[p][i]; // 回溯上一状态
            currentState.cost -= cost[p][i];     // 回溯上一状态
        }
    }
}

int main()
{
    input();
    backtrack(1); // 回溯
    cout << minWeight << endl;
    for (int i = 1; i <= n; ++i) // 输出结果
        cout << result[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}