/*****************************************************************//**
 * \file   2-6.cpp
 * \brief  �㷨�����е��ֵ�������
 * \author Hyoung Yan
 * \date   2024 03 14 
 *********************************************************************/
#include<iostream>
#include<algorithm>
using namespace std;
/// @brief �ݹ鷽������׳�
/// @param n 
/// @return �׳˽��
int factorial(int n)
{
	if (n <= 1)return 1;
	else
		return factorial(n - 1) * n;
}
///// @brief ���㵱ǰ���������������е�˳��
///// @param data ��������
///// @param n    ���г���
///// @return ��ǰ���е�˳��
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

/// @brief ���㵱ǰ���������������е�˳�򣨵ݹ�ʵ�֣�
/// @param data ��������
/// @param n    ���г���
/// @return ��ǰ���е�˳��
int order(int* data, int n) {
	if (n <= 1) return 0;
	int count = 0;
	for (int i = 1; i < n; ++i) {
		if (data[0] > data[i]) count++;
	}
	return count * factorial(n - 1) + order(data + 1, n - 1);
}

/// @brief ������ data ����һ���ֵ������д洢�� data ��
/// @param data ��������
/// @param n    ���г���
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
