#include<iostream>
#include<cstring>
using namespace std;
const int N = 1000;
int p[N];//父节点数组
int d[N][N];//邻接矩阵
int tc[N][N];//传递闭包

int find(int x)
{
	if (p[x] == x)return x;
	return p[x] = find(p[x]);
}
int main()
{
	for (int i = 0; i < N; i++)
	{
		p[i] = i;//初始化并查集，将每个节点的父节点设为自身
	}
	memset(d, 0, sizeof d);
	memset(tc, 0, sizeof tc);
	int n, m;//m为图的边数     结点数为n
	cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        d[u][v] = d[v][u] = d[u][u] = d[v][v] = 1; // 将边存入邻接矩阵
        if (p[u] == u && p[v] == v) {
            p[v] = u;//如果 u 和 v 都是根节点，直接将 v 的父节点设为 u
        }
        else if (p[u] == u && p[v] != v) {
            p[u] = find(v);//如果 u 是根节点而 v 不是，将 u 所在集合的代表节点设为 v 所在集合的代表节点
        }
        else if (p[u] != u && p[v] == v) {
            p[v] = find(u);//如果 u 不是根节点而 v 是，将 v 所在集合的代表节点设为 u 所在集合的代表节点
        }
        else {
            int x = find(u);
            int y = find(v);
            p[x] = y;//如果 u 和 v 都不是根节点，将 u 所在集合的代表节点设为 v 所在集合的代表节点
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = find(i), v = find(j);
            if (u == v && d[i][j] != 1) {
                tc[i][j] = 1;//遍历图的所有节点对，检查它们是否在同一个集合中且没有直接相连的边
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << tc[i][j] << ' ';
        }
        cout << endl;
    }
}