#include <iostream>
using namespace std;

int D[101][101]; // 第i行第j列的数字
int dp[101][101]; // 存储最大路径和
int n; // 三角形列数

int maxs(int x, int y) {
    return (x > y ? x : y);
}
/**
 * \brief  动态规划求解三角形最大路径和
 * \return 返回顶部最大路径和
 */
int MaxSum() {
    // 初始化最底部的dp值为三角形底部的值
    for (int j = 1; j <= n; ++j)
        dp[n][j] = D[n][j];
    // 自底向上计算最大路径和
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = maxs(dp[i + 1][j], dp[i + 1][j + 1]) + D[i][j];
        }
    }
    return dp[1][1]; // 返回顶部的最大路径和
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            cin >> D[i][j];
    cout << MaxSum() << endl;
    return 0;
}
