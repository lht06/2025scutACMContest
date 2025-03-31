#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=5010;
double dp[2][N];
void solve()
{   
    int x,y;
    cin>>x>>y;
    int a=(x+7)/8,b=(y+7)/8;
    for (int i=0;i<=b;i++) dp[0][i]=dp[1][i]=0;
    for (int i=0;i<=a;i++)
        for (int j=0;j<=b;j++)
        {
            if (i&&j) dp[i&1][j]=0.5*dp[i&1^1][j]+0.5*dp[i&1][j-1]+1;
            else if (i) dp[i&1][j]=dp[i&1^1][j]+1;
            else dp[i&1][j]=0;
        }
    cout<<fixed<<setprecision(12)<<dp[a&1][b]<<"\n";
} 
signed main() 
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int t=1;
    cin>>t;
    while (t--) solve();
    return 0;
}
/*
dp(x,y)=0.5*dp(x-1,y)+0.5*dp(x,y-1)+1
*/