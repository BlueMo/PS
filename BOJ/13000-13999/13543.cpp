// 13543: 수열과 쿼리 2
// fail 1~?: query 함수가 int형이여서 답을 잘못 출력함
// 		   : 2^32 * 2^32 * a -> long long int 넘어감
//         : % 연산으로 인한 시간초과... -> 왜 이렇게 시간을 많이 잡아먹지? (web ide 환경으로 N,M=10^5 기준 2초 넘게 차이남)


#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef unsigned ll;


int N, M, c[12][12];
ll a, p[200002][12];

struct node
{
	node *l, *r, *p;		// left, right, parent
	int cnt;				// cnt(for find Kth)
	ll v;					// value
	ll eq[12];				// sum of Ai*(x+1)^k
	ll tmp[12];
	
	node(ll _v)
	{
		l = r = p = NULL;
		v = _v;
		for (int i = 0; i < 11; ++i) eq[i] = _v;
		cnt = 1;
	}
};

struct SplayTree
{
	node *root;
	
	int size(){ return root->cnt; }
	
	void update(node *x, bool calc_eq=true)
	{
		int k;
		k = x->cnt = 1;
		if (x->l)
		{
			x->cnt += x->l->cnt;
			if (calc_eq)
			{
				memcpy(x->tmp, x->l->eq, sizeof(x->tmp));
				k = x->cnt;
				for (int i = 0; i < 11; ++i)
				{
					for (int j = 0; j <= i; ++j) 
					{
						x->tmp[i] = (x->tmp[i] + x->v * c[i][j] * p[k-1][j]);
					}
				}
			}
		}
		else if (calc_eq)
		{
			for (int i = 0; i < 11; ++i) x->tmp[i] = x->v;
		}
		if (x->r)
		{
			if (calc_eq)
			{
				for (int i = 0; i < 11; ++i)
				{
					for (int j = 0; j <= i; ++j)
					{
						x->tmp[i] = (x->tmp[i] + x->r->eq[i-j] * c[i][j] * p[k][j]);
					}
				}
			}
			x->cnt += x->r->cnt;
		}
		
		if (calc_eq) memcpy(x->eq, x->tmp, sizeof(x->eq));
	}
	
	void rotate(node *x)
	{
		node *p = x->p;
		node *g = p->p;
		node *b = NULL;
		if (x == p->l)
		{
			p->l = b = x->r;
			x->r = p;
		}
		else
		{
			p->r = b = x->l;
			x->l = p;
		}
		x->p = g;
		p->p = x;
		if (b) b->p = p;
		if (!g) root = x;
		else if (g->l == p) g->l = x;
		else g->r = x;
		memcpy(x->eq, p->eq, sizeof(x->eq));
		update(p);
		update(x, false);
	}
	
	void splay(node *x, node *y = NULL)
	{
		while (x->p != y)
		{
			node *p = x->p;
			node *g = p->p;
			if (g != y)
			{
				if ( (g->l == p) == (p->l == x) ) rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
		if (!y) root = x;
	}
	
	node* findKth(int k)		// 0-based
	{
		node *x = root;
		while (1)
		{
			while (x->l && x->l->cnt > k) x = x->l;
			if (x->l) k -= x->l->cnt;
			if (!k) break;
			k--;
			x = x->r;
		}
		splay(x);
		return x;
	}
	
	void push(int k, ll val)
	{
		node *n = new node(val);
		if (!root)
		{
			root = n;
			return;
		}
		
		if (k != size())
		{
			findKth(k);
			if (root->l)
			{
				root->l->p = n;
				n->l = root->l;
			}
			root->l = n;
			n->p = root;
		}
		else
		{
			findKth(k-1)->r = n;
			n->p = root;
		}
		splay(n);
	}
	
	node* query(int l, int r)
	{
		if (r-l+1 == size()) return root;
		if (!l) return findKth(r + 1)->l;
		if (r+1 == size()) return findKth(l - 1)->r;
		return interval(l, r);
	}
	
	void pop(int k)
	{
		node *d = findKth(k);
		if (!d) return;
		if (d->l)
		{
			if (d->r)
			{
				root = d->l;
				root->p = NULL;
				node *x = root;
				while (x->r) x = x->r;
				x->r = d->r;
				d->r->p = x;
				
				x = x->r;
				while (x)
				{
					update(x);
					x = x->p;
				}
				
				delete d;
				return;
			}
			root = d->l;
			root->p = NULL;
			delete d;
			return;
		}
		if (d->r)
		{
			root = d->r;
			root->p = NULL;
			delete d;
			return;
		}
		delete d;
		root = NULL;
	}
	
	node* interval(int l, int r)
	{
		node *x = findKth(r + 1);
		findKth(l - 1);
		splay(x, root);
		return x->l;
	}
	
	void change(int k, ll val)
	{
		findKth(k);
		root->v = val;
		update(root);
	}
}A;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	c[0][0] = 1;
	for (int i = 1; i < 11; ++i)
	{
		c[i][0] = 1;
		for (int j = 1; j < i; ++j) c[i][j] = c[i-1][j-1] + c[i-1][j];
		c[i][i] = 1;
	}
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		p[i][0] = 1;
		for (int j = 1; j < 11; ++j) p[i][j] = (p[i][j-1] * i);
	}
	
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		A.push(i, a);
	}
	cin >> M;
	for (int i = N+1; i <= N+M; ++i)
	{
		p[i][0] = 1;
		for (int j = 1; j < 11; ++j) p[i][j] = (p[i][j-1] * i);
	}
	for (int i = 0; i < M; ++i)
	{
		int q;
		ll u, v, k;
		cin >> q;
		if (q == 1)
		{
			cin >> u >> v;
			A.push(u, v);
		}
		else if (q == 2)
		{
			cin >> u;
			A.pop(u);
		}
		else if (q == 3)
		{
			cin >> u >> v;
			A.change(u, v);
		}
		else
		{
			cin >> u >> v >> k;
			cout << A.query(u, v)->eq[k] << "\n";
		}
	}
	return 0;
}