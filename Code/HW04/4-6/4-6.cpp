#include<iostream>
#include<algorithm>
#include <iomanip>
using namespace std;

const int N = 100010;
int t[N],s[N];
int n;

int main()
{
    // ����˿�����
	cin >> n;
    // ����ÿ���˿���Ҫ�ķ���ʱ��
	for (int i = 1; i <= n; ++i)
		cin >> t[i];
    // ���˿͵ķ���ʱ�䰴����������
	sort(t + 1, t + n + 1);
    // ����ÿ���˿���ɷ���ʱ���ۼ�ʱ��
	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + t[i];
    // �����ܵȴ�ʱ��
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res += s[i];
    // ����ƽ���ȴ�ʱ��
	double ans = static_cast<double>(res) / n;
    // ��������������λС��
	cout << fixed << setprecision(2) << ans << endl;
	return 0;
}
