#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=1e6+10;
const int Mod=998244353;
char a[N],L[N],R[N];
int a_l,L_l,R_l;
long long dp[N],dpsum[N];
int zl[N],zr[N],ext_l[N],ext_r[N];

void get_zl(int n=L_l)
{
    int l=1,r=1;
    zl[1]=n; //undefined
    for(int i=2;i<=n;i++)
    {
        if(i<=r)
            zl[i]=min(zl[i-l+1],r-i+1);//init        
        while (i+zl[i]<=n && L[zl[i]+1]==L[i+zl[i]]) //i+z[i] is next position, so accessible pos is i+z[i]-1
            zl[i]++;
        if(i+zl[i]-1>r)
            l=i,r=i+zl[i]-1;
    }
}

void get_zr(int n=R_l)
{
    int l=1,r=1;
    zr[1]=n; //undefined
    for(int i=2;i<=n;i++)
    {
        if(i<=r)
            zr[i]=min(zr[i-l+1],r-i+1);//init        
        while (i+zr[i]<=n && R[zr[i]+1]==R[i+zr[i]]) //i+z[i] is next position, so accessible pos is i+z[i]-1
            zr[i]++;
        if(i+zr[i]-1>r)
            l=i,r=i+zr[i]-1;
    }
}

void exkmp_l(int m=a_l,int n=L_l) //get ext_l array
{
    while(ext_l[1]<=m && a[1+ext_l[1]]==L[1+ext_l[1]]) ext_l[1]++;
    int l=1,r=1;
    for(int i=2;i<=m;i++)
    {
        if(i<=r)
            ext_l[i]=min(zl[i-l+1],r-i+1);
        while (i+ext_l[i]<=m && L[ext_l[i]+1]==a[i+ext_l[i]]) 
            ext_l[i]++;
        if(i+ext_l[i]-1>r)
            l=i,r=i+ext_l[i]-1;
    }
}

void exkmp_r(int m=a_l,int n=R_l) //get ext_r array
{
    while(ext_r[1]<=m && a[1+ext_r[1]]==R[1+ext_r[1]]) ext_r[1]++;
    int l=1,r=1;
    for(int i=2;i<=m;i++)
    {
        if(i<=r)
            ext_r[i]=min(zr[i-l+1],r-i+1);
        while (i+ext_r[i]<=m && R[ext_r[i]+1]==a[i+ext_r[i]]) 
            ext_r[i]++;
        if(i+ext_r[i]-1>r)
            l=i,r=i+ext_r[i]-1;
    }
}

bool check_r(int j)
{
    int pos=j-R_l+1 ;
    if(ext_r[pos]==R_l) return true;
    int next_pos=pos+ext_r[pos];
    if(a[next_pos]<=R[ext_r[pos]+1]) return true;
    return false;
}

bool check_l(int j)
{
    int pos=j-L_l+1 ;
    if(ext_l[pos]==L_l) return true;
    int next_pos=pos+ext_l[pos];
    if(a[next_pos]>=L[ext_l[pos]+1]) return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>a+1>>L+1>>R+1;
    L_l=strlen(L+1);
    R_l=strlen(R+1);
    a_l=strlen(a+1);
    dp[0]=dpsum[0]=1; //gran
    get_zl();
    get_zr();
    exkmp_l();
    exkmp_r();
    for(int j=1;j<=a_l;j++)
    {
        int ll=j-R_l,rr=j-L_l;
        if(ll<0) ll=0;
        else if(check_r(j)==false) ll++;

        if(rr>=j-1) rr=j-2;
        else if(check_l(j)==false) rr--;

        if(ll<=rr)
        {
            dp[j]+=dpsum[rr];
            if(ll-1>=0) dp[j]-=dpsum[ll-1];
            dp[j]%=Mod;
        }
        if(L_l==1 && L[1]<=a[j])
            {dp[j]+=dp[j-1];dp[j]%=Mod;}
        if(R_l==1 && R[1]<a[j])
            {dp[j]-=dp[j-1];dp[j]%=Mod;}
        dpsum[j]=dpsum[j-1];
        if(j+1<=a_l && a[j+1]!='0') {dpsum[j]+=dp[j];dpsum[j]%=Mod;}
    }
    cout<<(dp[a_l]+Mod)%Mod<<endl; //!!
    return 0;
}