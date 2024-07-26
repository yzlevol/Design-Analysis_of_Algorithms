/*
 * @Description  :
 * @Author       : Hyoung
 * @Date         : 2024-05-06 17:41:34
 * @LastEditTime : 2024-05-06 22:06:57
 * @FilePath     : \Algorithm\Code\HW05\5-1.cpp
 */
#include <iostream>
using namespace std;

int a[1000];        // a[i] 表示集合S中的第 i 个元素
bool X[1000];       // X[i] 如果为 true，表示 a[i] 在子集S1中
int tw = 0, rw = 0; // tw: 子集S1的元素之和, rw: 剩余元素的和
bool flag = false;  // 标志位，用于表示是否找到解
int n, c;           // n: 集合S的元素数量, c: 目标和

void backtrack(int i) // 回溯函数，i 表示当前考虑到的元素索引
{
    if (i >= n || flag == true) // 如果已经考虑完所有元素，或者已经找到解，就返回
        return;

    if (tw == c) // 如果子集S1的元素之和等于目标和，就输出解，并设置标志位为 true
    {
        for (int j = 0; j < i; ++j)
        {
            if (X[j] == true)
                cout << a[j] << " ";
        }
        flag = true;
        return;
    }

    // 如果加入当前元素不会超过目标和，就尝试加入
    if (tw + a[i] <= c) // 进入左子树，剪枝
    {
        X[i] = true;
        tw += a[i];
        rw -= a[i];
        backtrack(i + 1);
        tw -= a[i];
        rw += a[i];
    }

    // 如果即使不选择当前元素，剩余元素的和加上当前已选元素的和仍然能够达到目标和，就尝试不选择当前元素
    if (tw + rw - a[i] >= c) // 进入右子树，剪枝
    {
        X[i] = false;
        rw -= a[i];
        backtrack(i + 1);
        rw += a[i];
    }
}

int main()
{
    cin >> n >> c;              // 输入集合S的元素数量和目标和
    for (int i = 0; i < n; ++i) // 输入每个元素的值，并计算所有元素的总和
    {
        cin >> a[i];
        rw += a[i];
    }
    backtrack(0);      // 从第一个元素开始考虑，进行回溯
    if (flag == false) // 如果没有找到解，就输出 "No Solution!"
        cout << "No Solution!" << endl;
    cout << endl;
    system("pause");
    return 0;
}