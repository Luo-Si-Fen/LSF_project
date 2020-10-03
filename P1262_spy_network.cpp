//有向图缩点
#include <iostream>
#include <cstdio>
using namespace std;
const int N=3010,M=16010;
struct E
{
    int to,inext;
}edge[M],edge_c[M];
int head[N],total,head_c[N],total_c;

int dfn[N],low[N],dfn_cnt;
int st[N],st_p,scc_cnt,c[N]; //stack, scc_count
bool inst[N]; //in stack
int in_degree[N];
int c_val[N],a[N]; // minval of a scc , initial value for each point

int n,p,r;

void adde(int x,int y)
{
    edge[++total].to=y;
    edge[total].inext=head[x];
    head[x]=total; //!
}

void adde_c(int x,int y)
{
    edge_c[++total_c].to=y;
    edge_c[total_c].inext=head_c[x];
    head_c[x]=total_c;
}

void tarjan(int x)
{
    dfn[x]=low[x]=++dfn_cnt;
    st[++st_p]=x, inst[x]=true;
    for(int e=head[x];e;e=edge[e].inext)
    {
        int y=edge[e].to;
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(inst[y])
            low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) //scc
    {
        scc_cnt++;
        c_val[scc_cnt]=1145141919;
        int y;
        do
        {
            y=st[st_p--]; //!
            inst[y]=false;
            c[y]=scc_cnt;
            c_val[scc_cnt]=min(c_val[scc_cnt],a[y]); //update scc's minval
        } while (x!=y);
        
    }
}

void create_new_graph()
{
    for(int i=1;i<=n;i++)
    {
        for(int e=head[i];e;e=edge[e].inext)
        {
            int y=edge[e].to;
            if(c[y]!=c[i])
            {
                adde_c(c[i],c[y]);
                in_degree[c[y]]++;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>p;
    for(int i=1;i<=n;i++)
        a[i]=1145141919;
    for(int i=1;i<=p;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x]=y;
    }
    cin>>r;
    for(int i=1;i<=r;i++)
    {
        int x,y;
        cin>>x>>y;
        adde(x,y);
    }
    for(int i=1;i<=n;i++) // 阻止没法被收买的点tarjan
        if(!dfn[i] && a[i]<1145141919) tarjan(i);
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            cout<<"NO"<<endl;
            cout<<i<<endl;
            return 0;
        }
    }
    create_new_graph();
    long long ans=0;
    for(int i=1;i<=scc_cnt;i++)
    {
        if(in_degree[i]==0)
        {
            ans+=c_val[i];
        }
    }
    cout<<"YES"<<endl;
    cout<<ans<<endl;
    return 0;
}