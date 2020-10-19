//exkmp n
#include <iostream>
#include <cstdio>
#include <memory.h>
#include <cstring>
using namespace std;
int T;
const int N=1e6+5;
const long long Mod=1e9+7;
char b[N];
int z[N],b_l;
int delta_num[N],num[N];

void get_z(int n=b_l)
{
    int l=1,r=1;
    z[1]=b_l;
    for(int i=2;i<=n;i++)
    {
        if(i<=r)
            z[i]=min(z[i-l+1],r-i+1);
        while (i+z[i]<=n && b[z[i]+1]==b[i+z[i]])
            z[i]++;
        if(i+z[i]-1>r)
            l=i,r=i+z[i]-1;
    }
}

void do_delta_num(int n=b_l)
{
    for(int i=2;i<=n;i++)
    {
        if(z[i]<i)
        {
            delta_num[i]+=1;
            delta_num[i+z[i]]-=1;
        }
        else
        {
            delta_num[i]+=1;
            delta_num[i+i-1]-=1;
        }
    }
    for(int i=2;i<=n;i++)
        num[i]=num[i-1]+delta_num[i];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while (T--)
    {
        cin>>b+1;
        b_l=strlen(b+1);
        memset(delta_num,0,sizeof(delta_num));
        memset(z,0,sizeof(z));
        get_z();
        do_delta_num();
        long long ans=1;
        for(int i=1;i<=b_l;i++)
        {
            ans*=(num[i]+1)%Mod;
            ans%=Mod;
        }
        cout<<ans<<endl;
    }
    
    return 0;
}