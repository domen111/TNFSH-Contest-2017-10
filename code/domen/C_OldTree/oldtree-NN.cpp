#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
int n;
int v[100001];
//bool g2[10001][10001];
vector<int> g[100001];
bool u[100001]={};
int dfs(int i)
{
	u[i]=1;
	int sz=v[i];
	for(int j:g[i])
		if(!u[j])
			sz+=dfs(j);
	return sz;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int m;
	cin>>n>>m;
	assert(n<=100000 && m<=(long long)n*(n+1)/2 && m<=1000000 && n>=1 && m>=n);
	for(int i=1;i<=n;i++)
	{
		cin>>v[i];
		assert(v[i]<=10000);
	}
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		assert(a>=0 && b>=0 && a<=n && b<=n);
		//assert(g[a][b]==0);
		//g[a][b]=g[b][a]=1;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	int mn = dfs(0), ans=-1;
	for(int i=0;i<=n;i++) // check connectivity
		assert(u[i]==1);
	for(int i=1;i<=n;i++)
	{
		memset(u,0,sizeof u);
		u[i]=1;
		int t = dfs(0);
		if(t<mn)
		{
			ans=i;
			mn=t;
		}
	}
	cout<<ans<<endl;
}