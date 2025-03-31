#include<bits/stdc++.h>
using namespace std;
const int N=300010,INF=1e9;
vector<int> g[N];
int n,val[N],d[N];
int depth[N],dfn[N],sz[N],fa[N],top[N],son[N],cnt;
int root[N],idx;
namespace io {
    namespace detail {
      const size_t buflen = (1 << 21) + 1;
      char buf[buflen], *st = nullptr, *ed = nullptr;
      inline char gc() { return ((st == ed) ? (st = buf, ed = st + fread(buf, 1, buflen, stdin), (st == ed) ? EOF : *st++) : *st++); }
      inline bool blank(char c) { return c == ' ' || c == '-' || c == '\n' || c == '\t' || c == '\r'; }
      template <typename T> inline bool Re(T &x) {
        char c; int f = 1;
        while (blank(c = gc())) if (c == '-') f = -1;
        if (c == EOF) return false;
        for (x = c - '0'; (c = gc()) >= '0' && c <= '9'; x = x * 10 + c - '0');
        x *= f; return true;
      }
      char obuf[buflen], *_ptr = obuf, *_oed = obuf + buflen - 1, _stk[55];
      int _top;
      void flush() { fwrite(obuf, 1, _ptr - obuf, stdout); _ptr = obuf;}
      void pc(char c) { *(_ptr++) = c; if (_ptr == _oed) flush(); }
      template <typename T> inline void Pr(T x) {
        if (x == 0) { pc('0'); return; }
        if (x < 0) { pc('-'); x = -x; }
        for (_top = 0; x > 0; _top++, x /= 10) _stk[_top] = (x % 10) + '0';
        while (_top > 0) pc(_stk[--_top]);
      }
      template <typename T> inline void Prln(T x) { Pr(x); pc('\n'); }
      struct _IOflusher_ { ~_IOflusher_() { flush(); } } __flusher__;
    }  // namespace detail
    struct instream {
      instream &operator>>(char &__n) { __n = detail::gc(); return *this; }
      instream &operator>>(unsigned char &__n) { __n = detail::gc(); return *this; }
      instream &operator>>(short &__n) { detail::Re(__n); return *this; }
      instream &operator>>(unsigned short &__n) { detail::Re(__n); return *this; }
      instream &operator>>(int &__n) { detail::Re(__n); return *this; }
      instream &operator>>(unsigned int &__n) { detail::Re(__n); return *this; }
      instream &operator>>(long &__n) { detail::Re(__n); return *this; }
      instream &operator>>(unsigned long &__n) { detail::Re(__n); return *this; }
      instream &operator>>(long long &__n) { detail::Re(__n); return *this; }
      instream &operator>>(unsigned long long &__n) { detail::Re(__n); return *this; }
    #ifdef __SIZEOF_INT128__
      instream &operator>>(__int128 &__n) { detail::Re(__n); return *this;}
      instream &operator>>(__uint128_t &__n) { detail::Re(__n); return *this; }
    #endif
      instream &operator>>(std::string &__n) {
        __n.clear();
        char c = detail::gc();
        if(c == EOF) return *this;
        while(c != EOF && detail::blank(c)) c = detail::gc();
        if(c == EOF) return *this;
        while(c != EOF && !detail::blank(c)) {
          __n.push_back(c);
          c = detail::gc();
        }
        if(c != EOF) detail::st--;
        return *this;
      }
    } in;
    struct outstream {
      outstream &operator<<(const char &__n) { detail::pc(__n); return *this; }
      outstream &operator<<(const unsigned char &__n) { detail::pc(__n); return *this; }
      outstream &operator<<(const short &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const unsigned short &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const int &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const unsigned int &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const long &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const unsigned long &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const long long &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const unsigned long long &__n) { detail::Pr(__n); return *this; }
    #ifdef __SIZEOF_INT128__
      outstream &operator<<(const __int128 &__n) { detail::Pr(__n); return *this; }
      outstream &operator<<(const __uint128_t &__n) { detail::Pr(__n); return *this; }
    #endif
      outstream &operator<<(const std::string &__n) {
        for(const char &__c: __n) detail::pc(__c);
        return *this;
      }
    } out;
    }  // namespace io
    using io::in;
    using io::out;
struct Dynamic_Tree
{
    int l,r,cnt,is_exist;
}dtr[N*8];
struct Node
{
    int l,r;
    int minv;
}tr[N<<2];
void dfs(int u,int father,int dep)
{
    sz[u]=1,fa[u]=father,depth[u]=dep;
    for (int j:g[u])
    {
        if (j==father) continue;
        dfs(j,u,dep+1);
        sz[u]+=sz[j];
        if (sz[j]>sz[son[u]]) son[u]=j;
    }
}
void dfs(int u,int t)
{
    dfn[u]=++cnt,top[u]=t;
    if (!son[u]) return ;
    dfs(son[u],t);
    for (int j:g[u])
    {
        if (j==fa[u]||j==son[u]) continue;
        dfs(j,j);
    }
}
void build(int u,int l,int r)
{
    if (l==r) tr[u]={l,r};
    else
    {
        tr[u]={l,r};
        int mid=l+r>>1;
        build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    }
}
void pushup(int u)
{
    tr[u].minv=min(tr[u<<1].minv,tr[u<<1|1].minv);
}
void modify(int u,int x,int v)
{
    if (tr[u].l==tr[u].r) tr[u].minv=v;
    else
    {
        int mid=tr[u].l+tr[u].r>>1;
        if (x<=mid) modify(u<<1,x,v);
        else modify(u<<1|1,x,v);
        pushup(u);
    }
}
int query(int u,int l,int r)
{
    if (l>r) return INF;
    if (l<=tr[u].l&&r>=tr[u].r) return tr[u].minv;
    else
    {   
        int mid=tr[u].l+tr[u].r>>1,res=INF;
        if (l<=mid) res=min(res,query(u<<1,l,r));
        if (r>mid) res=min(res,query(u<<1|1,l,r));
        return res;
    }
}
int modify(int p,int l,int r,int x,int val)
{
    if (!p) p=++idx;
    if (l==r)
    {
        dtr[p].cnt+=val;
        dtr[p].is_exist=dtr[p].cnt>0;
        return p;
    }
    int mid=l+r>>1;
    if (x<=mid) dtr[p].l=modify(dtr[p].l,l,mid,x,val);
    else dtr[p].r=modify(dtr[p].r,mid+1,r,x,val);
    dtr[p].is_exist=dtr[dtr[p].l].is_exist+dtr[dtr[p].r].is_exist;
    return p;
}
void modify(int u,int v)
{
    int x=u;
    while (x)
    {
        int tar=top[x];
        if (fa[tar]==0) break;
        int old_min=query(1,dfn[tar],dfn[tar]+sz[tar]-1);
        root[fa[tar]]=modify(root[fa[tar]],0,d[fa[tar]],old_min,-1);
        x=fa[tar];
    }
    x=u;
    modify(1,dfn[x],v);
    val[x]=v;
    while (x)
    {
        int tar=top[x];
        if (fa[tar]==0) break;
        int new_min=query(1,dfn[tar],dfn[tar]+sz[tar]-1);
        root[fa[tar]]=modify(root[fa[tar]],0,d[fa[tar]],new_min,1);
        x=fa[tar];
    }
}
int query_mex(int p,int l,int r)
{
    if (l==r) return l;
    int mid=l+r>>1;
    if (dtr[dtr[p].l].is_exist!=mid-l+1) return query_mex(dtr[p].l,l,mid);
    else return query_mex(dtr[p].r,mid+1,r);
}
int query(int u)
{
    vector<int> v;
    if (fa[u]) v.push_back(min(query(1,1,dfn[u]-1),query(1,dfn[u]+sz[u],n)));
    if (son[u]) v.push_back(query(1,dfn[son[u]],dfn[son[u]]+sz[son[u]]-1));
    for (int x:v)
        if (0<=x&&x<=d[u]) root[u]=modify(root[u],0,d[u],x,1);
    int res=query_mex(root[u],0,d[u]);
    for (int x:v)
        if (0<=x&&x<=d[u]) root[u]=modify(root[u],0,d[u],x,-1);
    return res;
}
void solve()
{
    in>>n;
    for (int i=1;i<=n;i++) in>>val[i];
    for (int i=0;i<n-1;i++)
    {
        int a,b;
        in>>a>>b;
        d[a]++,d[b]++;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1,0,1);
    dfs(1,1);
    build(1,1,n);
    for (int i=1;i<=n;i++) modify(1,dfn[i],val[i]);
    for (int i=1;i<=n;i++)
        for (int j:g[i])
            if (j!=fa[i]&&j!=son[i])
            {
                int t=query(1,dfn[j],dfn[j]+sz[j]-1);
                if (0<=t&&t<=d[i]) root[i]=modify(root[i],0,d[i],query(1,dfn[j],dfn[j]+sz[j]-1),1);
            }
    int q;
    in>>q;
    while (q--)
    {
        int t,x;
        in>>t>>x;
        if (t==1)
        {
            int v;
            in>>v;
            modify(x,v);
        }
        else out<<query(x)<<"\n";
    }
}
int main()
{
    solve();
    return 0;
}