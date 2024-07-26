/*****************************************************************//**
 * \file   1-3.cpp
 * \brief  
 * \author Hyoung Yan
 * \date   2024 03 04 
 *********************************************************************/
#include <iostream>
using namespace std;

/// @brief 求约数个数
/// @param x 
/// @return 
int div(int x)
{
	int sum = 0;
	for (int i = 1; i <= x; ++i) {
		if(x%i==0)
			sum++;
	}
	return sum;
}

int main()
{ 
	int a, b, maxNum = 0;
	int tmp = 0;
	cin >> a >> b;
	for (int i = a; i <= b; ++i) {
		tmp=div(i);
		if(tmp>maxNum)
			maxNum=tmp;
	}
	cout << maxNum << endl;
	return 0;
}
