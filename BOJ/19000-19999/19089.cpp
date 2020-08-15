/* 13974: 파일 합치기 2
 * Garsia-Wachs
 * Splay Tree
 */

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int T, N, a[200005];
ll ans;

struct node
{
	node *l, *r, *p;	// left, right, parent
	int v;				// value
	int cnt;
	
	node(int _v)
	{
		l = r = p = NULL;
		v = _v;
		cnt = 1;
	}
};

void DFS(node *p)
{
	cout << p->v << " ";
	if (p->l)
	{
		cout << "L ";
		DFS(p->l);
		cout << p->v << " ";
	}
	if (p->r)
	{
		cout << "R ";
		DFS(p->r);
		cout << p->v << " ";
	}
}

void DFS2(node *p)
{
	if (p->r)
		DFS2(p->r);
	cout << p->v << " ";
	if (p->l)
		DFS2(p->l);
}

void printTree(node *x)
{
	if (!x)
	{
		cout << "NULL" << endl;
		return;
	}
	DFS(x);
	cout << endl;
}

void printArray(node *x)
{
	if (!x)
	{
		cout << "NULL" << endl;
		return;
	}
	DFS2(x);
	cout << endl;
}

struct SplayTree
{
	node *root;
	int size = -1;			// save real size-1 
	
	void update(node *x)
	{
		x->cnt = 1;
		if (x->l)
			x->cnt += x->l->cnt;
		if (x->r)
			x->cnt += x->r->cnt;
		size = x->cnt-1;
	}
	
	void rotate(node *x)
	{
		node *p = x->p;
		node *g = p->p;
		node *b = NULL;
		// move children x --> p
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
		// change x <--> p
		x->p = g;
		p->p = x;
		if (b) b->p = p;
		// update grand parent
		if (!g) root = x;
		else if (g->l == p) g->l = x;
		else g->r = x;
		// update cnt value
		update(p);
		update(x);
	}
	
	void splay(node *x)
	{
		/* Case
		 * 1. x->p is root 
			  : rotate(x) 
		 * 2. g-p-x direction is same 
		      : rotate(p), rotate(x)
		 * 3. direction is not same
		      : rotate(x), rotate(x)
		 */
		while (x->p)
		{
			node *p = x->p;
			node *g = p->p;
			if (p != root)
			{
				if ( (g->l == p) == (p->l == x) )	// Is it same direction?
					rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
	}
	
	int findKth(int k)	// 0-based	(max: 0, ... ,min: size-1)
	{
		node *x = root;
		
		if (k == -1) return 0x7fffffff;
		
		while (1)
		{
			while (x->r && x->r->cnt > k) x = x->r;
			if (x->r) k-= x->r->cnt;
			if (k == 0) break;
			k--;
			x = x->l;
		}
		splay(x);
		return x->v;
	}
	
	int lower_bound(int val)		// return k value should be placed (k is 0-based index)
	{
		/* 1. find lower_bound node: p
		 * 2. splay(p)
		 * 3. p->l->cnt: # small node
		 */
		node *x = root;
		node *p = NULL;
		
		if (!x) return -1;
		
		int k;
		
		while (x)
		{
			if (val <= x->v)
			{
				k = 0;
				p = x;
				x = x->l;
			}
			else 
			{
				k = -1;
				p = x;
				x = x->r;
			}
		}
		k += size;
		splay(p);
		if (p->l)
			k -= p->l->cnt;
		return k;		// -1 : satisfy condition
	}
	
	node* splitLeft(int k)			// split left-sub tree and return its root ptr
	{
		node *l_root = NULL;
		
		if (k == size)		// split X
			return NULL;
		if (k == -1)		// all pop
		{
			l_root = root;
			root = NULL;
			size = -1;
			return l_root;
		}
		
		findKth(k);
		l_root = root->l;
		root->l = NULL;
		update(root);
		l_root->p = NULL;
		return l_root;
	}
	
	void mergeLeft(node* l_root)
	{
		if (!l_root) return;
		
		if (!root)
		{
			root = l_root;
			update(root);
			l_root = NULL;
			return;
		}
		
		findKth(size);		// now root is minimum value
		root->l = l_root;
		l_root->p = root;
		l_root = NULL;
		update(root);
	}

	void push(int val)
	{
		node *p = new node(val);
		if (!root)
		{
			root = p;
			size = 0;
			return;
		}
		
		node *x = root;
		while (1)		// left: <, right: >=
		{
			if (val < x->v)
			{
				if (!x->l)
				{
					x->l = p;
					p->p = x;
					break;
				}
				x = x->l;
			}
			else
			{
				if (!x->r)
				{
					x->r = p;
					p->p = x;
					break;
				}
				x = x->r;
			}
		}
		splay(p);
	}
	
	void pop()
	{
		findKth(size);
		
		node *x = root;	
		node *r = x->r;
	
		root = NULL;
		if (r)
		{
			r->p = NULL;
			root = r;
			update(root);
		}
		else
			size = -1;
		delete x;
	}
	
}even, odd;

void combine()
{
	ll sum = odd.findKth(odd.size) + even.findKth(even.size);
	ans += sum;
	
	odd.pop();
	even.pop();
	
	int even_pos = even.lower_bound(sum);
	int odd_pos = odd.lower_bound(sum);
	bool push_even = 0;
	
	if (even_pos < odd_pos)
	{
		even_pos = odd_pos;
		push_even = 1;
	}
	else if (even_pos > odd_pos)
	{
		odd_pos = even_pos-1;
		push_even = 0;
	}
	else
		push_even = 1;
	
	node *sub_even = even.splitLeft(even_pos);
	node *sub_odd = odd.splitLeft(odd_pos);	
	int new_back;
	
	while(1)
	{
		if (even.size == odd.size)
			new_back = even.findKth(even.size);
		else
			new_back = odd.findKth(odd.size);
		
		if (new_back <= sum)			// 조건 만족x -> 재귀호출
			combine();
		else
			break;
	}
	
	bool swapTree = 0;
	if (even.size <= odd.size)
	{
		even.push(sum);
		if (push_even)
			swapTree = 1;
	}
	else
	{
		odd.push(sum);
		if (!push_even)
			swapTree = 1;
	}
	
	if (swapTree)
	{
		even.mergeLeft(sub_odd);
		odd.mergeLeft(sub_even);
	}
	else
	{
		even.mergeLeft(sub_even);
		odd.mergeLeft(sub_odd);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	while(T--)
	{
		ans = 0;
		cin >> N;

		for (int i = 1; i <= N; ++i)
			cin >> a[i];
		
		even.push(a[1]);
		odd.push(a[2]);
		a[N+1] = 0x7fffffff-1;
		
		for (int i = 3; i <= N+1; ++i)
		{
			int back;
			while (1)
			{
				if (even.size <= odd.size)
					back = even.findKth(even.size);
				else
					back = odd.findKth(odd.size);
				
				/*
				cout << endl << "even: ";
				printArray(even.root);
				cout << " odd: ";
				printArray(odd.root);
				*/
				
				if (back <= a[i])
					combine();
				
				else
					break;
			}
			
			if (even.size <= odd.size)
				even.push(a[i]);
			else
				odd.push(a[i]);
		}
		cout << ans << endl;
		
		even.pop();
		odd.pop();
	}
	return 0;
}