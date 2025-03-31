#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1000000007;
using i64=long long;
i64 fact[20],infact[20];
vector<i64> countUpTo(i64 x) 
{
    vector<int> digits;
    for (auto t:to_string(x)) digits.push_back(t-'0');
    int len=digits.size();
    static i64 dp[20][2][2][1<<10];
    memset(dp,0,sizeof dp);
    dp[0][1][1][0]=1;
    for (int pos=0;pos<len;pos++) 
        for (int tight=0;tight<2;tight++) 
            for (int lead=0;lead<2;lead++) 
                for (int mask=0;mask<(1<<10);mask++) 
                {
                    i64 ways=dp[pos][tight][lead][mask];
                    if (!ways) continue;
                    int limit=tight?digits[pos]:9;
                    for (int dig=0;dig<=limit;dig++) 
                    {
                        int ntight=(tight&&(dig==limit))?1:0;
                        int nlead=(lead&&(dig==0))?1:0;
                        int nmask=mask;
                        if (!nlead) nmask=mask|(1<<dig);
                        dp[pos+1][ntight][nlead][nmask]=dp[pos+1][ntight][nlead][nmask]+ways;
                    }
                }
    vector<i64> res(1<<10,0);
    for (int tight=0;tight<2;tight++) 
        for (int lead=0;lead<2;lead++) 
            for (int mask=0;mask<(1<<10);mask++) 
            {
                i64 ways=dp[len][tight][lead][mask];
                if (!ways) continue;
                int finalMask=mask;
                if (lead) finalMask|=1;
                res[finalMask]=(res[finalMask]+ways)%mod;
            }
    return res;
}
vector<i64> getFCounts(i64 L,i64 R) 
{
    vector<i64> cntR=countUpTo(R),cntL=countUpTo(L-1),F(1<<10,0);
    for (int mask=0;mask<(1<<10);mask++) F[mask]=(cntR[mask]-cntL[mask]+mod)%mod;
    return F;
}
i64 qmi(i64 a,i64 b)
{
    i64 res=1;
    while (b)
    {
        if (b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
i64 C(i64 a,i64 b)
{
    if (a<b||a<0||b<0) return 0;
    if (a>=20)
    {
        i64 res=infact[b];
        for (i64 i=a-b+1;i<=a;i++) res=res*i%mod;
        return res;
    }
    else return fact[a]*infact[b]%mod*infact[a-b]%mod;
}
void solve()
{
    i64 L,R;
    int n,d;
    cin>>L>>R>>n>>d;
    vector<i64> F=getFCounts(L,R),f_req(1<<10,0);
    for (int req=0;req<(1<<10);req++)
        for (int sup=req;sup<(1<<10);sup=(sup+1)|req)
            f_req[req]=(f_req[req]+F[sup])%mod;
    i64 ans=0;
    for (int req=0;req<(1<<10);req++) 
    {
        int cntDigits=__builtin_popcount(req);
        if (cntDigits<d) continue;
        i64 ways=C(f_req[req],n);
        i64 coeff=C(cntDigits,d);
        if ((cntDigits-d)%2==1) coeff=(mod-coeff)%mod;
        ans=(ans+coeff*ways)%mod;
    }
    cout<<ans%mod<<"\n";
}
int main()
{
    fact[0]=1;
    for (int i=1;i<20;i++) fact[i]=fact[i-1]*i%mod;
    infact[19]=qmi(fact[19],mod-2);
    for (int i=18;i>=0;i--) infact[i]=infact[i+1]*(i+1)%mod;
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int t;
    cin>>t;
    while (t--) solve();
    return 0;
}