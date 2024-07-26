/*****************************************************************//**
 * \file   findKnums.cpp
 * \brief  
 * \author Hyoung Yan
 * \date   2024 03 13 
 *********************************************************************/
#include<iostream>
#include<vector>
using namespace std;
// @brief 基于快速排序的思想，找到数组中最小的k个数
// @param arr 数组
// @param left 左边界
// @param right 右边界
// @param k 
void sortK(vector<int>& arr,int left,int right,int k)
{
	if (left > right)
		return;
	int i = left,j=right,tmp = arr[left];
	while (i<j){
		//tmp作为枢轴变量，交换左右位置的元素
		while (i < j && arr[j] >= tmp)
			j--;
		while (i < j && arr[i] <= tmp)
			i++;
		if(i<j)
			swap(arr[i],arr[j]);
	}
	arr[left] = arr[i]; //将枢轴元素放到正确的位置
	arr[i] = tmp;

	if (i == k - 1) return;
	else if(i<k-1)
		return sortK(arr,i+1,right,k);//递归右边
	else 
		return sortK(arr,left,i-1,k);//递归左边
}
// @brief 调用sortK函数选出最小的k个数，并存在res中
// @param arr 
// @param k 
// @return 
vector<int> findKnums(vector<int>& arr, int k)
{
	vector<int> res;
	if (arr.size() < k)
		return res;
	sortK(arr,0,arr.size()-1,k);
	for (int i = 0; i < k; i++)
		res.push_back(arr[i]);//将最小的k个数放到res中
	return res;
}

int main()
{
	int n, k;
	cout << "n= ;k= ;" << endl;
	cin >> n >> k;
	vector<int> arr(n);
	cout<<"arr[]="<<endl;
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	vector<int> res = findKnums(arr,k);
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << " ";
	cout << endl;
	return 0;
}
