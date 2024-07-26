/*****************************************************************//**
 * \file   2-11.cpp
 * \brief  整数因子分解问题
 * \author Hyoung Yan
 * \date   2024年03月17日
 *********************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

int ans = 0;
/// @brief  递归函数，用于计算给定整数的因子数量
/// @param n  待分解的整数
void solve(int n)
{
    if (n == 1)
        ans++;
    else
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) {
                solve(i);
                if (i != n / i)
                    solve(n / i);
            }
        }
    if (n > 1) // 处理质数的情况
        ans++;
}

int main()
{
    int n;
    while (cin >> n) {
        ans = 0;
        solve(n);
        cout << ans << endl;
    }
    return 0;
}
