#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node
{
	int cw;//��ǰ����
	int cp;//��ǰ��ֵ
	int i;//��ǰ������
	int j;//�������
	node* parent;//���ڵ�

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

int n, m, d;//n��ʾ�������m��ʾ��������d��ʾ�������
int bestw;//��������
//lb[i]��ʾ��i���������n���������С����
vector<int>lb;
//bestx[i]��ʾ��i������ɵ�bestx[i]�����̼ӹ�
vector<int>bestx;
//w[i][j]��ʾ��i������ڵ�j�����̵�������c[i][j]��ʾ��i������ڵ�j�����̵ļ�ֵ
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
			cin >> c[i][j];//�����ֵ
		}
	}
	//����c[i][j]���ۼӺ�
	for (int i = 0; i < n; i++) {
		int minw = INT_MAX;		//��ʼ����С����Ϊ���ֵ
		for (int j = 0; j < m; j++) {
			cin >> w[i][j];//��������
			if (minw > w[i][j])
				minw = w[i][j];//�ҵ���С����
		}
		lb[i] = minw;//����С������ֵ��lb[i]
	}
	//����lb[i]���ۼӺ�
	for (int i = n - 2; i >= 0; --i) {
		lb[i] += lb[i + 1] + lb[i];
	}
	bestw = INT_MAX;
}

/**
 * brief: �����½�
 * \param n
 * \return ���ص�ǰ�ڵ����������ʣ���������С����
 */
int lowerBound(node tree) {
	//�����ǰ�ڵ������һ���ڵ㣬���ص�ǰ�ڵ������
	if (tree.i == n - 1)
		return tree.cw;
	//���ص�ǰ�ڵ����������ʣ���������С����
	return tree.cw + lb[tree.i + 1];
}

/**
 * brief: ��֧�޽編
 */
void BranchBound()
{
	priority_queue<node> pq;//���ȶ���
	node root(0, 0, -1, 0, NULL);//��ʼ��root�ڵ�
	pq.push(root);//��root�ڵ�ѹ�����ȶ���

	while (!pq.empty())
	{
		//ȡ����ǰ�ڵ�
		node* curNode = new node(pq.top());
		pq.pop();

		if (curNode->i == n - 1) {
			if (curNode->cw < bestw && curNode->cp <= d) {
				bestw = curNode->cw;
				for (node* k = curNode; k->i != -1; k = k->parent) {
					bestx[k->i] = k->j + 1;//��¼���Ž�
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
	//������
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