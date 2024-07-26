#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v; 
    int w;    
};

int findFather(vector<int>& father, int x) {
    if(father[x] == x) 
        return x;
	else 
        return father[x] = findFather(father, father[x]);
}

int kruskal(int N, vector<Edge>& edges) {
    vector<int> father(N + 1); 
    for (int i = 1; i <= N; ++i)
        father[i] = i;

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    int ans = 0, numEdges = 0;
    for (const Edge& e : edges) {
        int fu = findFather(father, e.u);
        int fv = findFather(father, e.v);
        if (fu != fv) {
            father[fu] = fv;
            ans += e.w;
            ++numEdges;
            if (numEdges == N - 1) break;
        }
    }

    return (numEdges == N - 1) ? ans : -1; 
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int minWeight = kruskal(N, edges);
    if (minWeight != -1)
        cout << minWeight << endl;
    else
        cout << "impossible" << endl;

    return 0;
}
