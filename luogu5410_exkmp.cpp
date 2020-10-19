#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=2e7+10;
char a[N],b[N];
int z[N],extend[N],a_l,b_l; // z function is for b

void get_z(int n=b_l)
{
    int l=1,r=1;
    z[1]=b_l; //undefined
    for(int i=2;i<=n;i++)
    {
        if(i<=r)
            z[i]=min(z[i-l+1],r-i+1);//init        
        while (i+z[i]<=n && b[z[i]+1]==b[i+z[i]]) //i+z[i] is next position, so accessible pos is i+z[i]-1
            z[i]++;
        if(i+z[i]-1>r)
            l=i,r=i+z[i]-1;
    }
}

void exkmp(int m=a_l,int n=b_l) //get extend array
{
    while(extend[1]<=m && a[1+extend[1]]==b[1+extend[1]]) extend[1]++;
    int l=1,r=1;
    for(int i=2;i<=m;i++)
    {
        if(i<=r)
            extend[i]=min(z[i-l+1],r-i+1);
        while (i+extend[i]<=m && b[extend[i]+1]==a[i+extend[i]]) 
            extend[i]++;
        if(i+extend[i]-1>r)
            l=i,r=i+extend[i]-1;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>a+1>>b+1;
    a_l=strlen(a+1);
    b_l=strlen(b+1);
    get_z();
    exkmp();
    /*for(int i=1;i<=a_l;i++)
        cout<<extend[i]<<" ";
    cout<<endl;
    for(int i=1;i<=b_l;i++)
        cout<<z[i]<<" ";*/
    long long ans1=0,ans2=0;
    for(int i=1;i<=b_l;i++)
        ans1^=(long long)i*(z[i]+1);
    for(int i=1;i<=a_l;i++)
        ans2^=(long long)i*(extend[i]+1);
    cout<<ans1<<endl<<ans2<<endl;
    
    return 0;
}