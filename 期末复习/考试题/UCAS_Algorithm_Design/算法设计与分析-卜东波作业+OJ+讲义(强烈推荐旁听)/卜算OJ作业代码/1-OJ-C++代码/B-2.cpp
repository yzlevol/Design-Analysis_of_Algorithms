#include <bits/stdc++.h> //万能头文件, 刷题时可以用, 大型项目千万不能用
using namespace std;
int a[10020];
int main(){
	int n,i,min,max;
	scanf("%d",&n);
	for(i=0;i<n;i++){ //杈撳叆
		scanf("%d",&a[i]);
	}
	max=a[0],min=a[0];//鏈�澶ф渶灏忓�煎垵濮嬭缃负鏁扮粍绗竴涓暟
	for(i=1;i<n;i++){
		if(a[i]<min){ //鎵炬渶澶�
			min=a[i];
		}
		if(a[i]>max){ //鎵炬渶灏�
			max=a[i];
		}
	}
	printf("%d",max-min);
}
