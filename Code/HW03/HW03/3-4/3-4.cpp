#include <iostream>
using namespace std;

int D[101][101]; // ��i�е�j�е�����
int dp[101][101]; // �洢���·����
int n; // ����������

int maxs(int x, int y) {
    return (x > y ? x : y);
}
/**
 * \brief  ��̬�滮������������·����
 * \return ���ض������·����
 */
int MaxSum() {
    // ��ʼ����ײ���dpֵΪ�����εײ���ֵ
    for (int j = 1; j <= n; ++j)
        dp[n][j] = D[n][j];
    // �Ե����ϼ������·����
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = maxs(dp[i + 1][j], dp[i + 1][j + 1]) + D[i][j];
        }
    }
    return dp[1][1]; // ���ض��������·����
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            cin >> D[i][j];
    cout << MaxSum() << endl;
    return 0;
}
