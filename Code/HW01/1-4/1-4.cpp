/*****************************************************************//**
 * \file   1-4.cpp
 * \brief  ��������ĳ�ʼ��Ŀ���Ҿ��󣬼���ﵽĿ��״̬����С����������
 *         ����Ĳ���������ת����һ�еĽ��״̬�򽻻��������еĽ�ҡ�
 * \author Hyoung Yan
 * \date   2024 03 05
 *********************************************************************/

#include<iostream>
#include<string.h> 
using namespace std;

#define MAXN 105 
const int inf = 0x3f3f3f3f; // ��ʾ�޽�����
int a[MAXN][MAXN], b[MAXN][MAXN], tmp[MAXN][MAXN]; // �ֱ�洢��ʼ״̬��Ŀ��״̬����ʱ״̬
int t, Col, Row; // ���԰�����������������

/// @brief ������н�ҵ�״̬�Ƿ���ͬ
/// @param num1 ��һ�е�����
/// @param num2 �ڶ��е�����
/// @return �������״̬��ͬ���򷵻�1�����򷵻�0
int check(int num1, int num2) {
    for (int i = 1; i <= Row; ++i) {
        if (a[i][num1] != b[i][num2])
            return 0;
    }
    return 1;
}

/// @brief ��תָ���еĽ��״̬
/// @param num Ҫ��ת���е�����
/// @details ��ָ���е�ÿ����ҵ�״̬���з�ת��0��1��1��0��
void changeRow(int num) {
    for (int i = 1; i <= Col; ++i) {
        b[num][i] ^= 1; // ͨ��������ʵ��״̬��ת
    }
}

/// @brief �������н�ҵ�λ�ã�������в�ͬ������н����������Ӳ�������
/// @param num1 ��һ�е�����
/// @param num2 �ڶ��е�����
/// @param step �������������ã����ڼ�¼�ܵĲ�������
void changeCol(int num1, int num2, int& step) {
    if (num1 == num2) return; // �����������ͬ������Ҫ����
    step++; 
    for (int i = 1; i <= Row; ++i) {
        int temp = b[i][num1];
        b[i][num1] = b[i][num2];
        b[i][num2] = temp;
    }
}

/// @brief ����ÿ�����԰���������ﵽĿ��״̬����С��������
/// @return ��С��������������޷��ﵽĿ��״̬�򷵻�-1
int findMinStep() {
    int ans = inf; 
    memcpy(tmp, b, sizeof(tmp)); 
    // ����ÿһ����Ϊ��ʼ�н����н���
    for (int k = 1; k <= Col; ++k) {
        int step = 0; // ��ǰ���ԵĲ���
        memcpy(b, tmp, sizeof(tmp)); // �ָ�b״̬
        changeCol(1, k, step); // ���Խ���һ�����k�н���
        // ����ÿ�У���鲢��ת��ƥ�����
        for (int i = 1; i <= Row; ++i) {
            if (a[i][1] != b[i][1]) {
                changeRow(i);
                step++;
            }
        }
        // ��鲢���Խ���ʣ�����
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
        // ����ҵ�һ�����еķ�����������С����
        if (found && step < ans) ans = step;
    }
    return ans < inf ? ans : -1; // ����ҵ��򷵻���С���������򷵻�-1
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
