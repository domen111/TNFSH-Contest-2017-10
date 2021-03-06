#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define endl '\n'


int w[100011];
vector<int> g[100011];

int dfn[100011];
int low[100011];
int sum[100011];

int next_dfn()
{
	static int _next_dfn = 0;
	return _next_dfn++;
}

void DFS(int i, int father)
{
	dfn[i] = next_dfn();
	sum[i] = w[i];
	low[i] = dfn[i]+1;
	for(int k=0; k<g[i].size(); k++)
	{
		int j = g[i][k];
		
		if(j==father)
			continue;
		
		if(dfn[j]==(-1))
		{
			DFS(j,i);
			low[i] = min( low[i], low[j] );
			if(low[j] >= dfn[j])
				sum[i] += sum[j];
		}
		else
			low[i] = min(low[i], dfn[j]);
	}
}

void Tarjan(int n)
{
	memset(dfn,-1,sizeof(dfn));
	dfn[0] = next_dfn();
	DFS(0,-1);
	/*
	puts("sum");
	for(int i=0; i<=n; i++)
		cout << sum[i] <<" ";
	cout <<endl;
	puts("dfn");
	for(int i=0; i<=n; i++)
		cout << dfn[i] <<" ";
	cout <<endl;	
	puts("low");
	for(int i=0; i<=n; i++)
		cout << low[i] <<" ";
	cout <<endl;	
	//	*/
}

int main()
{
	int n,m;
	cin >>n >> m;
	
	int total = 0;
	for(int i=1; i<=n; i++)
	{
		cin >> w[i];
		total += w[i];
	}
	
	int a,b;
	for(int i=0; i<m; i++)
	{
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	Tarjan(n);
	
	int max_sum = 0;
	int max_id = 0;
	for(int i=1; i<=n; i++)
	{
		if( sum[i] > max_sum )
		{
			max_sum = sum[i];
			max_id = i;
		}
	}
	
	cout << max_id << endl;
	
	
	return 0;
}



