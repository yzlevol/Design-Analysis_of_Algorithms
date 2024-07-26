/*****************************************************************//**
 * \file   1-4.cpp
 * \brief  解决给定的初始和目标金币矩阵，计算达到目标状态的最小操作步数。
 *         允许的操作包括翻转任意一行的金币状态或交换任意两列的金币。
 * \author Hyoung Yan
 * \date   2024 03 05
 *********************************************************************/

#include<iostream>
#include<string.h> 
using namespace std;

#define MAXN 105 
const int inf = 0x3f3f3f3f; // 表示无解的情况
int a[MAXN][MAXN], b[MAXN][MAXN], tmp[MAXN][MAXN]; // 分别存储初始状态、目标状态和临时状态
int t, Col, Row; // 测试案例数、列数、行数

/// @brief 检查两列金币的状态是否相同
/// @param num1 第一列的索引
/// @param num2 第二列的索引
/// @return 如果两列状态相同，则返回1；否则返回0
int check(int num1, int num2) {
    for (int i = 1; i <= Row; ++i) {
        if (a[i][num1] != b[i][num2])
            return 0;
    }
    return 1;
}

/// @brief 翻转指定行的金币状态
/// @param num 要翻转的行的索引
/// @details 将指定行的每个金币的状态进行翻转（0变1，1变0）
void changeRow(int num) {
    for (int i = 1; i <= Col; ++i) {
        b[num][i] ^= 1; // 通过异或操作实现状态翻转
    }
}

/// @brief 交换两列金币的位置，如果两列不同，则进行交换，并增加步数计数
/// @param num1 第一列的索引
/// @param num2 第二列的索引
/// @param step 操作步数的引用，用于记录总的操作步数
void changeCol(int num1, int num2, int& step) {
    if (num1 == num2) return; // 如果列索引相同，则不需要操作
    step++; 
    for (int i = 1; i <= Row; ++i) {
        int temp = b[i][num1];
        b[i][num1] = b[i][num2];
        b[i][num2] = temp;
    }
}

/// @brief 处理每个测试案例，计算达到目标状态的最小操作步数
/// @return 最小操作步数，如果无法达到目标状态则返回-1
int findMinStep() {
    int ans = inf; 
    memcpy(tmp, b, sizeof(tmp)); 
    // 尝试每一列作为初始列进行列交换
    for (int k = 1; k <= Col; ++k) {
        int step = 0; // 当前尝试的步数
        memcpy(b, tmp, sizeof(tmp)); // 恢复b状态
        changeCol(1, k, step); // 尝试将第一列与第k列交换
        // 遍历每行，检查并翻转不匹配的行
        for (int i = 1; i <= Row; ++i) {
            if (a[i][1] != b[i][1]) {
                changeRow(i);
                step++;
            }
        }
        // 检查并尝试交换剩余的列
        int found = 1;
        for (int i = 1; i <= Col && found; ++i) {
            found = 0;
            for (int j = i; j <= Col; ++j) {
                if (check(i, j)) {
                    changeCol(i, j, step);
                    found = 1;
                    break;
                }
            }
        }
        // 如果找到一个可行的方案，更新最小步数
        if (found && step < ans) ans = step;
    }
    return ans < inf ? ans : -1; // 如果找到则返回最小步数，否则返回-1
}

int main() {
    cin >> t;
    while (t--) {
        cin >> Row >> Col;
        for (int i = 1; i <= Row; ++i)
            for (int j = 1; j <= Col; ++j)
                cin >> a[i][j];
        for (int i = 1; i <= Row; ++i)
            for (int j = 1; j <= Col; ++j)
                cin >> b[i][j];
        cout << findMinStep() << endl;
    }
    return 0;
}
