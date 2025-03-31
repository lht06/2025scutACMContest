#include<bits/stdc++.h>
#define ll long long
using namespace std;
int f[2000010];
ll n,q;
ll find(ll x)
{
    if(f[x]==x)return x;
    f[x]=find(f[x]);
    return f[x];
}
void work()
{
    cin>>n>>q;
    for(int i=1;i<=n*2;i++)
    {
        f[i]=i;
    }
    while(q--)
    {
        ll opt,x1,y1,x2,y2;
        cin>>opt;
        if(opt==1)
        {
            cin>>x1>>y1;
            //f[find(x1)]=find(n+y1);
            f[find(n+y1)]=find(x1);
        }
        else
        {
            cin>>x1>>y1>>x2>>y2;
            if(find(x1)==find(x2))
            {
                cout<<"YES\n";
                continue;
            }
            if(find(x1)==find(n+y2))
            {
                cout<<"YES\n";
                continue;
            }
            if(find(n+y1)==find(x2))
            {
                cout<<"YES\n";
                continue;
            }
            if(find(n+y1)==find(n+y2))
            {
                cout<<"YES\n";
                continue;
            }
            cout<<"NO\n";
        }
    }
}
int main()
{
    //freopen("test013.in","r",stdin);freopen("test013.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while(T--)
    {
        work();
    }
    //fclose(stdin);fclose(stdout);
}