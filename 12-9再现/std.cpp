#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6010,mod=998244353;
int p[N],inv[N];
int qmi(int a,int b)
{
    int res=1;
    while (b)
    {
        if (b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
int C(int a,int b)
{
    if (a<0||b<0||a<b) return 0;
    return p[a]*inv[b]%mod*inv[a-b]%mod;
}
void solve()
{
    int K,p,q,n,m;
    cin>>K>>p>>q>>n>>m;
    if (max(n,m)>K) cout<<"0\n";
    else if (n==K&&m==K) cout<<"0\n";
    else if (n==0&&m==0) cout<<"1\n";
    else if (n==0&&m>0) cout<<"0\n";
    else if (m==K) cout<<"0\n";
    else
    {
        int Ps=p*qmi(p+q,mod-2)%mod,Pb=q*qmi(p+q,mod-2)%mod;
        int ans=0,all_game=n+m-1;
        //situation1:  scutsky:byyq = n:m
        ans+=C(all_game,n-1)*qmi(Ps,n)%mod*qmi(Pb,m)%mod;
        //situation2:  byyq:scutsky = n:m
        ans+=C(all_game,n-1)*qmi(Pb,n)%mod*qmi(Ps,m)%mod;
        ans%=mod;
        cout<<ans<<"\n";
    }
}
signed main()
{
    p[0]=1;
    for (int i=1;i<N;i++) p[i]=p[i-1]*i%mod;
    inv[N-1]=qmi(p[N-1],mod-2);
    for (int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int t=1;
    cin>>t;
    while (t--) solve();
    return 0;
}