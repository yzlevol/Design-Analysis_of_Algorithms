/*****************************************************************//**
 * \file   2-11.cpp
 * \brief  �������ӷֽ�����
 * \author Hyoung Yan
 * \date   2024��03��17��
 *********************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

int ans = 0;
/// @brief  �ݹ麯�������ڼ��������������������
/// @param n  ���ֽ������
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
    if (n > 1) // �������������
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
