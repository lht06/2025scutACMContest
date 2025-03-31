#include<bits/stdc++.h>
using namespace std;
using i64=long long;
const int N=300010,M=19;
int n,q,st[N][M],w[N];
i64 ans[N];
void init()
{
	for (int i=0;i<M;i++)
		for (int l=1;l+(1<<i)-1<=n;l++)
			if (!i) st[l][i]=w[l];
			else st[l][i]=__gcd(st[l][i-1],st[l+(1<<i-1)][i-1]);
}
int query(int l,int r)
{
    int k=__lg(r-l+1);
    return __gcd(st[l][k],st[r-(1<<k)+1][k]);
}
struct Node
{
	int l,r;
	i64 maxv,tag;
}tr[N<<2];
void pushup(int u)
{
	tr[u].maxv=max(tr[u<<1].maxv,tr[u<<1|1].maxv);
}
void build(int u,int l,int r)
{
	tr[u]={l,r};
	if (l==r) return ;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
void pushdown(int u)
{
	if (tr[u].tag)
	{
		i64 t=tr[u].tag;
		tr[u].tag=0;
		tr[u<<1].maxv=max(tr[u<<1].maxv,t);
		tr[u<<1|1].maxv=max(tr[u<<1|1].maxv,t);
		tr[u<<1].tag=max(tr[u<<1].tag,t);
		tr[u<<1|1].tag=max(tr[u<<1|1].tag,t);
	}
}
void modify(int u,int l,int r,i64 v)
{
	if (l<=tr[u].l&&r>=tr[u].r) tr[u].maxv=max(tr[u].maxv,v),tr[u].tag=max(tr[u].tag,v);
	else
	{
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if (l<=mid) modify(u<<1,l,r,v);
		if (r>mid) modify(u<<1|1,l,r,v);
		pushup(u);
	}
}
i64 query(int u,int l,int r)
{
	if (l<=tr[u].l&&r>=tr[u].r) return tr[u].maxv;
	else
	{
		pushdown(u);
		i64 mid=tr[u].l+tr[u].r>>1,res=0;
		if (l<=mid) res=max(res,query(u<<1,l,r));
		if (r>mid) res=max(res,query(u<<1|1,l,r));
		return res;
	}
}
vector<array<int,2>> Q[N];
i64 query_L(int L,int R)
{
	i64 res=0,pos=L+1;
	while (pos<=R)
	{
		i64 G=query(L,pos);
		int l=pos,r=R;
		while (l<r)
		{
			int mid=l+r+1>>1;
			if (query(L,mid)==G) l=mid;
			else r=mid-1;
		}
		res=max(res,G*(l-L+1)*(l-L+1));
		pos=l+1;
	}
	return max(res,(i64)query(L,R)*(R-L+1)*(R-L+1));
}
void solve()
{
	cin>>n>>q;
	for (int i=1;i<=n;i++) cin>>w[i],Q[i].clear();
	init();
	for (int i=1;i<=q;i++)
	{
		int l,r;
		cin>>l>>r;
		Q[r].push_back({l,i});
	}	
	build(1,1,n);
	for (int i=1;i<=n;i++)
	{
		int pos=i-1;
		while (pos>=1)
		{
			int G=query(pos,i),l=1,r=pos;
			while (l<r)
			{
				int mid=l+r>>1;
				if (query(mid,i)==G) r=mid;
				else l=mid+1;
			}
			modify(1,1,l,(i64)G*(i-l+1)*(i-l+1));
			pos=l-1;
		}
		for (auto [l,id]:Q[i]) ans[id]=max(query(1,l,i),query_L(l,i));
	}
	for (int i=1;i<=q;i++) cout<<ans[i]<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
	int t;
	cin>>t;
	while (t--) solve();
    return 0;
}