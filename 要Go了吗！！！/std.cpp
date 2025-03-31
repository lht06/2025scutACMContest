#include <bits/stdc++.h>
using namespace std;
const int N=1000010;
int ne[N][26],fa[N],cnt,LIM;
int f[N][2];
queue<array<int,2>>que;
void insert(string s,int st)
{
    int n=s.length();
    int p=0;
    for (int i=0;i<n;i++)
    {
        int ch=s[i]-'a';
        if (!ne[p][ch]) ne[p][ch]=++cnt;
        p=ne[p][ch];
    }
    if (f[p][0]>-1) return;
    f[p][0]=f[p][1]=st;
}
void build()
{
    queue<int>Que;
    for (int i=0;i<LIM;i++)
        if(ne[0][i]) Que.push(ne[0][i]);
    while (Que.size())
    {
        int u=Que.front();
        for (int i=0;i<LIM;i++)
        {
            if (ne[u][i])
            {
                fa[ne[u][i]]=ne[fa[u]][i];
                Que.push(ne[u][i]);
            }
            else ne[u][i]=ne[fa[u]][i];
        }
        Que.pop();
    }
} 
int he[N],to[N],nxt[N],idx;
void add(int u,int v)
{
    to[++idx]=v;
    nxt[idx]=he[u];
    he[u]=idx;
}
void trie_work(int u)
{
    for (int i=0;i<LIM;i++)
    {
        int v=ne[u][i];
        if (!v) return ;
        if (f[u][0]>f[v][0]) 
            f[v][0]=f[v][1]=f[u][0];
        trie_work(v);
    }
}
void fail_work(int u)
{
    for (int p=he[u];p;p=nxt[p])
    {
        int v=to[p];
        if (f[u][0]>f[v][0]) 
            f[v][0]=f[v][1]=f[u][0];
        fail_work(v);
    }
}
vector<int> edge[N];
int win_num[N][2];
void solve()
{
    int n,m;
    string s;
    char ch;
    cin>>n>>m>>ch;
    LIM=ch-'a'+1;
    while (n--) cin>>s,insert(s,1);
    while (m--) cin>>s,insert(s,0);
    
    trie_work(0);
    build();
    for (int i=1;i<=cnt;i++) add(fa[i],i);
    fail_work(0);
    for (int i=0;i<=cnt;i++)
        for (int j=0;j<LIM;j++) edge[ne[i][j]].push_back(i);
    for (int i=0;i<=cnt;i++)
        for (int j=0;j<2;j++) if (f[i][j]>-1) que.push({i,j});
    while (que.size())
    {
        auto [u,opt]=que.front(); que.pop();
        int val=f[u][opt];
        for (int v:edge[u])
        {
            if (f[v][opt^1]>-1) continue;
            if (opt==0&&val==0) 
            {
                win_num[v][0]++;
                if (win_num[v][0]==LIM) f[v][1]=0; 
            }
            if (opt==0&&val==1) f[v][1]=1;
            if (opt==1&&val==0) f[v][0]=0;
            if (opt==1&&val==1)
            {
                win_num[v][1]++;
                if (win_num[v][1]==LIM) f[v][0]=1;
            }
           
            if (f[v][opt^1]>-1) que.push({v,opt^1});
            
        }
    }
    if (f[0][1]==1) cout<<"scutsky\n";
    else if (f[0][1]==0) cout<<"byyq\n";
    else cout<<"draw\n";

    for (int i=0;i<=cnt;i++)
    {
        edge[i].clear();
        f[i][0]=f[i][1]=-1;
        win_num[i][0]=win_num[i][1]=0;
        memset(ne[i],0,sizeof ne[i]);
        fa[i]=he[i]=0;
    }
    
    cnt=idx=0;
}
signed main()
{
    memset(f,-1,sizeof f);
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T=1;
    cin>>T;
    while (T--) solve();
    return 0;
}