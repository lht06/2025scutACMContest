#include<bits/stdc++.h>
using namespace std;
std::mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
int rd(int l,int r)
{
    return std::uniform_int_distribution<int>(l,r)(myrand);
}
void solve()
{
    int n,m;
    cin>>n>>m;
    if (m==0) cout<<string(1,'a')+string(n-1,'b')<<"\n";
    else if (m==n-1) cout<<string(n,'a')<<"\n";
    else if (2*m<n) cout<<string(m,'a')+string(n-2*m,'b')+string(m,'a')<<"\n";
    else
    {
        int l=0,r=n-1,period=n-m;
        while (l<r)
        {
            int mid=l+r+1>>1;
            if (m>=mid)
            {
                period=__gcd(period,n-mid);
                l=mid;
            }
            else r=mid-1;
        }

        l=0,r=n-1;
        while (l<r)
        {
            int mid=l+r+1>>1;
            if (m>=mid) l=mid;
            else
            {
                int other_period=n-mid;
                if (other_period%period==0)
                {
                    cout<<"-1\n";
                    return ;
                }
                r=mid-1;
            }
        }
        if (period!=n-m)
        {
            cout<<"-1\n";
            return ;
        }
        while (true)
        {
            string base;
            for (int i=1;i<=period;i++) base+=rd('a','z');
            string ans;
            while (ans.size()<n) ans+=base;
            while (ans.size()>n) ans.pop_back();
            bool flag=true;
            int l=0,r=n-1;
            while (l<r)
            {
                int mid=l+r+1>>1;
                if (m>=mid)
                {
                    l=mid;
                    if (ans.substr(0,mid)!=ans.substr(n-mid,mid))
                    {
                        flag=false;
                        break;
                    }
                }
                else
                {
                    r=mid-1;
                    if (ans.substr(0,mid)==ans.substr(n-mid,mid))
                    {
                        flag=false;
                        break;
                    }
                }
            }
            if (flag)
            {
                cout<<ans<<'\n';
                return ;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int t=1;
    cin>>t;
    while (t--) solve();
    return 0;
}