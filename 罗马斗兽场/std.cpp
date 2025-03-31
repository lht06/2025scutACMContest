#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005,INF=2e18L,mod=998244353;
int f[N],ans[N],p2[N];
//f[N]表示一个n的顶点的凸包，在不考虑边缘连接的情况下，有多少种合法方案
void solve()
{
    int n;
    cin>>n;
    //2*f[i]*f[n-i+2]表示在不考虑边缘连接的情况下，有多少种小A能通过的合法方案
    //2表示1-i绳索是否连接的两种情况，1-i绳索把凸包分为了i个顶点的凸包和n-i+2个顶点的凸包
    //i=1，2，n时无需x2，用f[n]-f[i]*f[n-i+2]亦可表示，但为了简洁直接赋值
    for (int i=3;i<=n-1;i++)
        ans[i]=(f[n]-2*f[i]*f[n-i+2]%mod+mod)*p2[n]%mod;
    ans[1]=ans[2]=ans[n]=0;
    for (int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}
signed main()
{
    f[1]=f[2]=1;
    for (int i=3;i<=5000;i++)
    {
        f[i]+=f[i-1];
        for (int j=3;j<=i-1;j++)
            f[i]=(f[i]+f[j]*f[i-j+1]*2)%mod; 
    }
    p2[0]=1;
    for (int i=1;i<=5000;i++) p2[i]=p2[i-1]*2%mod;
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T=1;
    cin>>T;
    while (T--) solve();
    return 0;
}