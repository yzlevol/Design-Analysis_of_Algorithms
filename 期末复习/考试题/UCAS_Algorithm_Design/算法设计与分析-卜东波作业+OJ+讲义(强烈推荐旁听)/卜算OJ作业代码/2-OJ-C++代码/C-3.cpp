#include <bits/stdc++.h> //����ͷ�ļ�, ˢ��ʱ������, ������Ŀǧ������
using namespace std;
int main() 
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
	vector<int> odd;
    for(int i = 0; i < n; i++) {
		if(a[i] % 2 == 1) {
			odd.push_back(a[i]);
		}
	}
	sort(odd.begin(), odd.end());
	for(int i = 0; i < odd.size(); i++) {
		if(i == odd.size() - 1) {
			printf("%d", odd[i]);
		}
		else {
			printf("%d,", odd[i]);
		}
	}
}
