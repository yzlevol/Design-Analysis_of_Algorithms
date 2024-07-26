/*****************************************************************//**
 * \file   最大多位整数.cpp
 * \brief  最大多位整数
 * \author Hyoung
 * \date   2024 04 18
 *********************************************************************/
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int main(){
	vector<string> num;
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string temp;
		cin >> temp;
		num.push_back(temp);
	}
	for (int i = 0; i < n - 1; i++) {
		for (int k = i + 1; k < n; ++k) {
			if (num[i] + num[k] < num[k] + num[i]) {
				string temp = num[i];
				num[i] = num[k];
				num[k] = temp;
			}
		}
	}
	for (int i = 0; i != num.size(); i++) {
		cout<<num[i];
	}
}
