#include <bits/stdc++.h> //����ͷ�ļ�, ˢ��ʱ������, ������Ŀǧ������
using namespace std;
int main()
{
    int cows[55] = {0, 1, 2, 3, 4};
    int n;
    for(int i = 5; i < 55; i++)
        cows[i] = cows[i-1] + cows[i-3];
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        printf("%d\n", cows[n]);
    }
    return 0;
}
