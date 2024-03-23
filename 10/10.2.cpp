#include<iostream>
#include<cstring>
using namespace std;
const int N = 1000;
int p[N];//���ڵ�����
int d[N][N];//�ڽӾ���
int tc[N][N];//���ݱհ�

int find(int x)
{
	if (p[x] == x)return x;
	return p[x] = find(p[x]);
}
int main()
{
	for (int i = 0; i < N; i++)
	{
		p[i] = i;//��ʼ�����鼯����ÿ���ڵ�ĸ��ڵ���Ϊ����
	}
	memset(d, 0, sizeof d);
	memset(tc, 0, sizeof tc);
	int n, m;//mΪͼ�ı���     �����Ϊn
	cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        d[u][v] = d[v][u] = d[u][u] = d[v][v] = 1; // ���ߴ����ڽӾ���
        if (p[u] == u && p[v] == v) {
            p[v] = u;//��� u �� v ���Ǹ��ڵ㣬ֱ�ӽ� v �ĸ��ڵ���Ϊ u
        }
        else if (p[u] == u && p[v] != v) {
            p[u] = find(v);//��� u �Ǹ��ڵ�� v ���ǣ��� u ���ڼ��ϵĴ���ڵ���Ϊ v ���ڼ��ϵĴ���ڵ�
        }
        else if (p[u] != u && p[v] == v) {
            p[v] = find(u);//��� u ���Ǹ��ڵ�� v �ǣ��� v ���ڼ��ϵĴ���ڵ���Ϊ u ���ڼ��ϵĴ���ڵ�
        }
        else {
            int x = find(u);
            int y = find(v);
            p[x] = y;//��� u �� v �����Ǹ��ڵ㣬�� u ���ڼ��ϵĴ���ڵ���Ϊ v ���ڼ��ϵĴ���ڵ�
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = find(i), v = find(j);
            if (u == v && d[i][j] != 1) {
                tc[i][j] = 1;//����ͼ�����нڵ�ԣ���������Ƿ���ͬһ����������û��ֱ�������ı�
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