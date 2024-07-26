/*****************************************************************//**
 * \file   calendar.cpp
 * \brief  �����ճ̱�
 * \author Hyoung Yan
 * \date   2024 03 14 
 *********************************************************************/
#include<iostream>
#include<iomanip>
using namespace std;

int a[1001][1001];
int b[1001];
/// @brief nΪż��copy
/// @param n 
void copyeven(int n)
{
	int m=n/2;
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= m; j++){
			a[i][j + m] = a[i][j] + m;//���Ͻ�
			a[i + m][j]= a[i][j + m];//���½�
			a[i + m][j + m]=a[i][j];//���½�
		}
	}
}
/// @brief nΪ����copy
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
			a[i][m + j] = b[i + j - 1];//���Ͻ�
			a[b[i+j-1]][m + j] = i;//���½�
		}
	}
}
/// @brief �ݹ麯��
/// @param n 
void schedule(int n)
{
	if (n == 1) { //��ֹ����
		a[1][1] = 1;
		return;
	}
	if (n % 2)
		n++;
	schedule(n / 2);
	if (n / 2 > 1 && (n / 2) % 2 != 0) 
		copyodd(n); //nΪ����ʱ
	else 
		copyeven(n);//nΪż��ʱ
}
int main()
{
	int n;
	cin >> n;
	schedule(n); //���õݹ麯�����д���
	//����ճ̱��ر�������ʱ�����
	int m = n; //��������ʱ+1�ı�����
	bool flag = true;//ż����־
	if (n % 2 == 1) {
		m++;
		flag = false;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!flag && a[i][j] == m) {
				cout<<"  *";//����ѡ��
			}
			else
				cout<<setw(3)<<a[i][j] ;//��ʽ�����
		}
		cout << endl;
	}
	return 0;
}
