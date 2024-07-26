/*****************************************************************//**
 * \file   findKnums.cpp
 * \brief  
 * \author Hyoung Yan
 * \date   2024 03 13 
 *********************************************************************/
#include<iostream>
#include<vector>
using namespace std;
// @brief ���ڿ��������˼�룬�ҵ���������С��k����
// @param arr ����
// @param left ��߽�
// @param right �ұ߽�
// @param k 
void sortK(vector<int>& arr,int left,int right,int k)
{
	if (left > right)
		return;
	int i = left,j=right,tmp = arr[left];
	while (i<j){
		//tmp��Ϊ�����������������λ�õ�Ԫ��
		while (i < j && arr[j] >= tmp)
			j--;
		while (i < j && arr[i] <= tmp)
			i++;
		if(i<j)
			swap(arr[i],arr[j]);
	}
	arr[left] = arr[i]; //������Ԫ�طŵ���ȷ��λ��
	arr[i] = tmp;

	if (i == k - 1) return;
	else if(i<k-1)
		return sortK(arr,i+1,right,k);//�ݹ��ұ�
	else 
		return sortK(arr,left,i-1,k);//�ݹ����
}
// @brief ����sortK����ѡ����С��k������������res��
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
		res.push_back(arr[i]);//����С��k�����ŵ�res��
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
