/*****************************************************************//**
 * \file   2-6.cpp
 * \brief  算法：排列的字典序问题
 * \author Hyoung Yan
 * \date   2024 03 14 
 *********************************************************************/
#include<iostream>
#include<algorithm>
using namespace std;
/// @brief 递归方法计算阶乘
/// @param n 
/// @return 阶乘结果
int factorial(int n)
{
	if (n <= 1)return 1;
	else
		return factorial(n - 1) * n;
}
///// @brief 计算当前排列在所有排列中的顺序
///// @param data 排列数据
///// @param n    排列长度
///// @return 当前排列的顺序
//int order(int* data, int n)
//{
//	int res = 0;
//	for (int i = 0; i < n; ++i) {
//		int a = data[i];
//		int count = 0;
//		for (int j = i + 1; j < n; ++j) {
//			if (a > data[j])++count;
//		}
//		res += count * factorial(n - i - 1);
//	}
//	return res;
//}

/// @brief 计算当前排列在所有排列中的顺序（递归实现）
/// @param data 排列数据
/// @param n    排列长度
/// @return 当前排列的顺序
int order(int* data, int n) {
	if (n <= 1) return 0;
	int count = 0;
	for (int i = 1; i < n; ++i) {
		if (data[0] > data[i]) count++;
	}
	return count * factorial(n - 1) + order(data + 1, n - 1);
}

/// @brief 将排列 data 的下一个字典序排列存储在 data 中
/// @param data 排列数据
/// @param n    排列长度
void nextOrder(int* data, int n)
{
	int i = n - 2;
	while (i >= 0 && data[i] >= data[i + 1]) i--;
	if (i >= 0) {
		int j = n - 1;
		while (data[j] <= data[i]) j--;
		swap(data[i], data[j]);
		reverse(data + i + 1, data + n);
	}
}

int main()
{
	int* data = new int[1000];
	int n;
	while (cin >> n){
		for (int i = 0; i < n; ++i)
			cin >> data[i];
		cout << order(data, n) << endl;
		nextOrder(data, n);
		for (int i = 0; i < n; ++i)
			cout<<data[i]<<" ";
		cout << endl;
	}
	delete[] data;
	return 0;
}
