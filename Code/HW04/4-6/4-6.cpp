#include<iostream>
#include<algorithm>
#include <iomanip>
using namespace std;

const int N = 100010;
int t[N],s[N];
int n;

int main()
{
    // 输入顾客数量
	cin >> n;
    // 输入每个顾客需要的服务时间
	for (int i = 1; i <= n; ++i)
		cin >> t[i];
    // 将顾客的服务时间按照升序排序
	sort(t + 1, t + n + 1);
    // 计算每个顾客完成服务时的累计时间
	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + t[i];
    // 计算总等待时间
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res += s[i];
    // 计算平均等待时间
	double ans = static_cast<double>(res) / n;
    // 输出结果，保留两位小数
	cout << fixed << setprecision(2) << ans << endl;
	return 0;
}
