#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

using namespace std;

const int MAX_N = 1000;
const int MAX_K = 1000;

int n, k;//n��ʾ��������k��ʾ������
int Time[MAX_N];//ÿ�������ʱ��
int bestT = INT_MAX; // ����ʱ��

struct Node {
    int time[MAX_K]; // ��ǰ����������ʱ��
    int d; // ��ǰ�������
	int maxtime;// ��ǰ���ʱ��
	// ����<��������������ȶ��еıȽ�
    bool operator<(const Node& a) const {
        return maxtime > a.maxtime;
    }
};
/**
 * brief: ���ȶ��нⷨ
 */
int pq() {
    priority_queue<Node> pq;
    // ��ʼ��
    Node p;
    for (int i = 0; i < k; i++)
        p.time[i] = 0;
    p.d = 0;
    p.maxtime = 0;
    pq.push(p);
	// ���ȶ���ѭ��
    while (!pq.empty()) {
        p = pq.top();
        pq.pop();
		// ��֦
        if (p.maxtime >= bestT) 
            continue;
		// ����Ҷ�ڵ�,��������ʱ��
        if (p.d == n) {
            bestT = p.maxtime; 
            continue;
        }
		// �ݹ飬�������з�֧
        for (int i = 0; i < k; ++i) {
            Node next = p;
			next.d = p.d + 1;// ����������ţ���һ��
			next.time[i] += Time[next.d]; // ���»���ʱ��
			next.maxtime = max(next.time[i], p.maxtime);// �������ʱ��
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
