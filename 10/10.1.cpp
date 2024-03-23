#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N = 10e5;
int dist[N];
int matrix[100][100];
int n, m;
void bfs()
{
	memset(dist, -1, sizeof dist);
	dist[1] = 0;
	queue<int>queue;
	queue.push(1);
	while (queue.size())
	{
		int idx = queue.front();
		queue.pop();
		for (int i = 1; i <= n; i++)
		{
			if (matrix[idx][m] == 1)
			{
				dist[m] = dist[idx] + 1;
				return;
			}
			if (matrix[idx][i] == 1 && dist[i] == -1)
			{
				dist[i] = dist[idx] + 1;
				queue.push(i);
			}
		}
	}
}
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		matrix[a][b] = 1;
	}
	bfs();
	cout << dist[m];
}