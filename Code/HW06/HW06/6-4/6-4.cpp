#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node
{
	int cw;//当前重量
	int cp;//当前价值
	int i;//当前零件序号
	int j;//厂商序号
	node* parent;//父节点

	node(int cw, int cp, int i, int j, node* parent)
		: cw(cw), cp(cp), i(i), j(j), parent(parent) {}
	bool operator < (const node& a) const {
		if (a.cw != cw)
			return cw > a.cw;
		else if (a.i != i)
			return a.i > i;
		else
			return j > a.j;
	}
};

int n, m, d;//n表示零件数，m表示厂商数，d表示最大重量
int bestw;//最优重量
//lb[i]表示第i个零件到第n个零件的最小重量
vector<int>lb;
//bestx[i]表示第i个零件由第bestx[i]个厂商加工
vector<int>bestx;
//w[i][j]表示第i个零件在第j个厂商的重量，c[i][j]表示第i个零件在第j个厂商的价值
vector<vector<int>>w, c;

void init_MinWeight() {
	cin >> n >> m >> d;
	bestx.resize(n);
	lb.resize(n);
	w.resize(n);
	c.resize(n);
	for (int i = 0; i < n; i++) {
		w[i].resize(m);
		c[i].resize(m);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> c[i][j];//输入价值
		}
	}
	//计算c[i][j]的累加和
	for (int i = 0; i < n; i++) {
		int minw = INT_MAX;		//初始化最小重量为最大值
		for (int j = 0; j < m; j++) {
			cin >> w[i][j];//输入重量
			if (minw > w[i][j])
				minw = w[i][j];//找到最小重量
		}
		lb[i] = minw;//将最小重量赋值给lb[i]
	}
	//计算lb[i]的累加和
	for (int i = n - 2; i >= 0; --i) {
		lb[i] += lb[i + 1] + lb[i];
	}
	bestw = INT_MAX;
}

/**
 * brief: 计算下界
 * \param n
 * \return 返回当前节点的重量加上剩余零件的最小重量
 */
int lowerBound(node tree) {
	//如果当前节点是最后一个节点，返回当前节点的重量
	if (tree.i == n - 1)
		return tree.cw;
	//返回当前节点的重量加上剩余零件的最小重量
	return tree.cw + lb[tree.i + 1];
}

/**
 * brief: 分支限界法
 */
void BranchBound()
{
	priority_queue<node> pq;//优先队列
	node root(0, 0, -1, 0, NULL);//初始化root节点
	pq.push(root);//将root节点压入优先队列

	while (!pq.empty())
	{
		//取出当前节点
		node* curNode = new node(pq.top());
		pq.pop();

		if (curNode->i == n - 1) {
			if (curNode->cw < bestw && curNode->cp <= d) {
				bestw = curNode->cw;
				for (node* k = curNode; k->i != -1; k = k->parent) {
					bestx[k->i] = k->j + 1;//记录最优解
				}
			}
		}
		else {
			for (int j = 00; j < m; ++j) {
				node child(curNode->cw + w[curNode->i + 1][j], curNode->cp + c[curNode->i + 1][j], curNode->i + 1, j, curNode);
				if (child.cp <= d && lowerBound(child) < bestw)
					pq.push(child);
			}
		}
	}
	//输出结果
	if (bestw == INT_MAX) {
		cout << "No solution" << endl;
		return;
	}
	cout << bestw << endl;
	for (int i = 0; i < n; i++) {
		cout << bestx[i] << " ";
	}
}

int main()
{
	init_MinWeight();
	BranchBound();
	return 0;
}