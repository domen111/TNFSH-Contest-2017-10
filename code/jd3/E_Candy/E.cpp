#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define endl '\n'

struct SegTree
{
	int count = 0;
	int width = 0;
	int *a=nullptr;
	
	int leaf(int i){ return width+i; };
	int lch(int i){ return (i<<1); }
	int rch(int i){ return (i<<1)+1; }
	
	int GetMax(){ return a[1]; }
	
	void Up(int i){
		a[i] = max(a[lch(i)], a[rch(i)]);
	};
	
	void UpAll()
	{
		for(int i=width-1; i>=1; i--)
			Up(i);
	}
	
	
	void Init(int n)
	{
		width = 1;
		while(width < n)
			width <<= 1;
		count = width*2-1;
		a = new int[count+1];
		
		for(int i=1; i<=count; i++)
			a[i] = 0;
	}
	
	void Add(int x, int i)
	{
		i = leaf(i);
		a[i] += x;
		while(i>1)
		{
			i>>=1;
			Up(i);
		}
	}
	
	void _Mod(int i, int L, int R, int l, int r, int v)
	{
		if(L==l && R==r)
		{
			if(a[i] < v)
				return;
			if(L==R)
			{
				a[i] %= v;
				return;
			}
		}
		
		int M = ((L+R)>>1);
		if(r<=M)
			_Mod(lch(i), L,M, l,r, v);
		else if(M<l)
			_Mod(rch(i), M+1,R, l,r, v);
		else
		{
			_Mod(lch(i), L,M, l,M, v);
			_Mod(rch(i), M+1,R, M+1,r, v);
		}
		
		Up(i);
		
		return;
	}
	
	void Mod(int L, int R, int v)
	{
		_Mod(1, 0,width-1, L,R, v);
	}
};


int main()
{
	SegTree ST;
	
	int n;
	cin >> n;
	
	ST.Init(n);
	
	int a;
	for(int i=0; i<n; i++)
		cin >> ST.a[ST.leaf(i)];
	
	ST.UpAll();
	/*
	cout << "ST_size = " << ST.count <<endl;
	for(int i=1; i<=ST.count; i++)
	{
		if((i&(-i))==i)
			cout << endl;
		cout << ST.a[i] << " ";
	}
	*/
	int m;
	cin >> m;
	while(m--)
	{
		int K;
		cin >> K;
		if(K==1)
		{
			int x,i;
			cin >> x >> i;
			ST.Add(x,i);
		}
		else if(K==2)
		{
			int L,R,v;
			cin >> L >> R >> v;
			ST.Mod(L,R,v);
		}
		else // K==3
		{
			cout << ST.GetMax() << endl;
		}
	}
	
	return 0;
}



