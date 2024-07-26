/*****************************************************************//**
 * \file   calendar.cpp
 * \brief  网球日程表
 * \author Hyoung Yan
 * \date   2024 03 14 
 *********************************************************************/
#include<iostream>
#include<iomanip>
using namespace std;

int a[1001][1001];
int b[1001];
/// @brief n为偶数copy
/// @param n 
void copyeven(int n)
{
	int m=n/2;
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= m; j++){
			a[i][j + m] = a[i][j] + m;//右上角
			a[i + m][j]= a[i][j + m];//左下角
			a[i + m][j + m]=a[i][j];//右下角
		}
	}
}
/// @brief n为奇数copy
/// @param n 
void copyodd(int n)
{
	int m = n / 2;
	for (int i = 1; i <= m; ++i) {
		b[i] = m + i;
		b[m + i] = b[i];
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m + 1; j++) {
			if (a[i][j] > m) {
				a[i][j] = b[i];
				a[m+i][j] = (b[i]+m)%n;
			}
			else {
				a[m + i][j] = a[i][j] + m;
			}
		}
		for (int j = 2; j <= m; j++) {
			a[i][m + j] = b[i + j - 1];//右上角
			a[b[i+j-1]][m + j] = i;//左下角
		}
	}
}
/// @brief 递归函数
/// @param n 
void schedule(int n)
{
	if (n == 1) { //终止条件
		a[1][1] = 1;
		return;
	}
	if (n % 2)
		n++;
	schedule(n / 2);
	if (n / 2 > 1 && (n / 2) % 2 != 0) 
		copyodd(n); //n为奇数时
	else 
		copyeven(n);//n为偶数时
}
int main()
{
	int n;
	cin >> n;
	schedule(n); //调用递归函数进行处理
	//输出日程表，特别是奇数时的输出
	int m = n; //用于奇数时+1改变列数
	bool flag = true;//偶数标志
	if (n % 2 == 1) {
		m++;
		flag = false;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!flag && a[i][j] == m) {
				cout<<"  *";//虚拟选手
			}
			else
				cout<<setw(3)<<a[i][j] ;//格式化输出
		}
		cout << endl;
	}
	return 0;
}
