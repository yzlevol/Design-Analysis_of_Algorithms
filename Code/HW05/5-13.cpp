/*
 * @Description  :
 * @Author       : Hyoung
 * @Date         : 2024-05-06 14:29:38
 * @LastEditTime : 2024-05-07 00:12:21
 * @FilePath     : \Algorithm\Code\HW05\5-13.cpp
 */
#include <iostream>
using namespace std;

int n;                // 工作数量
int cost[21][21];     // 第 i 个人做第 j 个工作的花费
int Min = 0x7fffffff; // 最小花费,先初始化为最大值
int sumCost = 0;      // 当前花费
int flag[21];         // 标记是否已经被分配工作了
/**
 * @brief 回溯法求解最小花费
 * @param p 当前前考虑的人
 */
void backtrack(int p)
{
    if (p >= n) // 如果已经考虑完所有人，就返回
    {
        if (Min > sumCost) // 如果当前花费小于最小花费，就更新最小花费
        {
            Min = sumCost;
            return;
        }
    }
    // 如果当前花费已经大于最小花费，就不用再继续分配工作了
    for (int i = 0; i < n; ++i)
    {
        if (flag[i] == 0) // 如果第 i 个工作还没有被分配
        {
            flag[i] = 1;
            sumCost += cost[p][i];
            if (sumCost < Min) // 如果当前花费小于最小花费，就继续分配工作
                backtrack(p + 1);
            flag[i] = 0;
            sumCost -= cost[p][i]; // 回溯
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> cost[i][j];
        }
        flag[i] = 0;
    }
    backtrack(0);
    cout << Min << endl;
    system("pause");
    return 0;
}