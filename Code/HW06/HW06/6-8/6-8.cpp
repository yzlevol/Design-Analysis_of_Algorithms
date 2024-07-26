#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

using namespace std;

const int MAX_N = 1000;
const int MAX_K = 1000;

int n, k;//n表示任务数，k表示机器数
int Time[MAX_N];//每个任务的时间
int bestT = INT_MAX; // 最优时间

struct Node {
    int time[MAX_K]; // 当前各个机器的时间
    int d; // 当前任务序号
	int maxtime;// 当前最大时间
	// 重载<运算符，用于优先队列的比较
    bool operator<(const Node& a) const {
        return maxtime > a.maxtime;
    }
};
/**
 * brief: 优先队列解法
 */
int pq() {
    priority_queue<Node> pq;
    // 初始化
    Node p;
    for (int i = 0; i < k; i++)
        p.time[i] = 0;
    p.d = 0;
    p.maxtime = 0;
    pq.push(p);
	// 优先队列循环
    while (!pq.empty()) {
        p = pq.top();
        pq.pop();
		// 剪枝
        if (p.maxtime >= bestT) 
            continue;
		// 到达叶节点,更新最优时间
        if (p.d == n) {
            bestT = p.maxtime; 
            continue;
        }
		// 递归，遍历所有分支
        for (int i = 0; i < k; ++i) {
            Node next = p;
			next.d = p.d + 1;// 更新任务序号，下一层
			next.time[i] += Time[next.d]; // 更新机器时间
			next.maxtime = max(next.time[i], p.maxtime);// 更新最大时间
            pq.push(next);
        }
    }
    return bestT;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> Time[i];
    cout << pq() << endl;
    return 0;
}
