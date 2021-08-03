#include <bits/stdc++.h>
using namespace std;

/*
Contains a Class Template implementation of Segment Trees

SegmentTree<class T> (const vector<T>&arr, T (*fncptr)(T,T), T error_code)

Arguments:
arr -> Array on which range queries need to be performed
(*fncptr) -> Funcion pointer to the function used in range queries
error_code -> Value to return if query is illegal.
*/

template <typename T>
class SegmentTree
{
	vector<T>tree;
	T (*func)(T,T);
	vector<T>A;
	T illegal;

public:

	SegmentTree(const vector<T>&arr, T (*fncptr)(T,T), T error_code)
	{
		func = fncptr;
		A = arr;
		illegal = error_code;
		tree.resize(4*A.size());
		build(0,0,A.size()-1);
	}

	void build(int v, int l, int r)
	{
		//cout<<v<<" ";
		if (l==r)
		{
			tree[v] = A[l];
			return;
		}

		int mid = (l+r)/2;
		build(2*v+1,l,mid);
		build(2*v+2,mid+1,r);

		tree[v] = func(tree[2*v+1], tree[2*v+2]);
	}

	void update(int v, int pos, int l, int r,const T &x)
	{
		if (pos<l || pos>r)
			return;

		if (l==r)
		{
			A[pos] = x;
			tree[v] = x;
			return;
		}

		int mid = (l+r)/2;
		update(2*v+1, pos, l,mid,x);
		update(2*v+2,pos, mid+1,r ,x);
		tree[v] = func(tree[2*v+1], tree[2*v+2]);
	}

	T findNum(int v, int tl, int tr, int l, T r)
	{
		//cout<<v<<" ";
		if (r<tl || l>tr || tl>tr)
			return illegal;

		if (tl>=l && tr<=r)
			return tree[v];

		int mid = (tl+tr)/2;
		T left = findNum(2*v+1, tl,mid, l,r);
		T right = findNum(2*v+2, mid+1, tr, l, r);

		if (left!=illegal && right!=illegal)
			return func(left,right);
		else if (left!=illegal)
			return left;
		else if (right!=illegal)
			return right;

		return illegal;
	}

	void query_update(int a, T b)
	{
		update(0,a-1,0,A.size()-1,b);
		return;
	}

	void query_RangeQuery(int a, int b)
	{
		cout<<findNum(0,0,A.size()-1,a-1,b-1)<<endl;
		return;
	}

};

int comparefunc(int a, int b)
{
	if (a<b)
		return a;
	else 
		return b;
}

int main()
{
	int n,q;
	cin>>n>>q;
	vector<int>A(n);
	for(int i=0; i<n; i++)
		cin>>A[i];
	
	SegmentTree<int> tree(A,comparefunc, INT_MAX);

	for(int i=0; i<q; i++)
	{
		char c;
		int a,b;
		cin>>c>>a>>b;
		if (c=='q')
			query_RangeQuery(a,b);
		else if (c=='u')
			query_update(a,b);
	}
	
	return 0;
}