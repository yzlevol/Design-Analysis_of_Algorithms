#include <bits/stdc++.h> //����ͷ�ļ�, ˢ��ʱ������, ������Ŀǧ������
using namespace std;
int a[10020];
int main(){
	int n,i,min,max;
	scanf("%d",&n);
	for(i=0;i<n;i++){ //输入
		scanf("%d",&a[i]);
	}
	max=a[0],min=a[0];//最大最小值初始设置为数组第一个数
	for(i=1;i<n;i++){
		if(a[i]<min){ //找最大
			min=a[i];
		}
		if(a[i]>max){ //找最小
			max=a[i];
		}
	}
	printf("%d",max-min);
}
