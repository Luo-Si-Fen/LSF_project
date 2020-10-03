// 和luogu 3275 重复 （有向图tarjan缩点）
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N=2e5+5; //数组得开大
struct E
{
    int to,inext,w;
}edge[2*N],edge_c[2*N];
int head[N],head_c[N],total,total_c;

int dfn[N],low[N],dfn_cnt;
int st[N],st_p,scc_cnt,c[N]; //stack, scc_count
bool inst[N]; //in stack
int in_degree[N];

int n,k;

void adde(int x,int y,int w)
{
    edge[++total].to=y;
    edge[total].w=w;
    edge[total].inext=head[x];
    head[x]=total;
}

void adde_c(int x,int y,int w)
{
    edge_c[++total_c].to=y;
    edge_c[total_c].w=w;
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
        int y;
        do
        {
            y=st[st_p--];
            inst[y]=false;
            c[y]=scc_cnt;
        } while (x!=y);
    }
}

int create_new_graph()
{
    for(int i=0;i<=n;i++)
    {
        for(int e=head[i];e;e=edge[e].inext)
        {
            int y=edge[e].to,w=edge[e].w;
            if(c[y]==c[i])
            {
                if(w) return -1;
            }
            else
            {
                adde_c(c[i],c[y],w);
                in_degree[c[y]]++;
            }
        }
    }
    return 0;
}

int f[N];
long long ans=0;
void topo()
{
    queue<int> q;
    for(int i=1;i<=scc_cnt;i++)
        if(in_degree[i]==0) q.push(i);
    while (q.size())
    {
        int x=q.front();
        q.pop();
        for(int e=head_c[x];e;e=edge_c[e].inext)
        {
            int y=edge_c[e].to,w=edge_c[e].w;
            f[y]=max(f[y],f[x]+w);
            //ans=max(ans,f[y]);
            in_degree[y]--;
            if(in_degree[y]==0) q.push(y);
        }
    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        int x,a,b;
        cin>>x>>a>>b;
        if(x==1) //=
        {
            adde(a,b,0);
            adde(b,a,0);
        }
        else if(x==2) //<
        {
            adde(a,b,1);
        }
        else if(x==3)
        {
            adde(b,a,0);
        }
        else if(x==4)
        {
            adde(b,a,1);
        }
        else
        {
            adde(a,b,0);
        }
    }
    for(int i=1;i<=n;i++)
        adde(0,i,1);
    for(int i=0;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    int result=create_new_graph();
    if(result==-1) //positive circles exist
    {
        cout<<-1<<endl;
        return 0;
    }
    else
    {
        topo();
        for(int i=0;i<=n;i++)
            ans+=f[c[i]];
        cout<<ans<<endl;
    }
    
    return 0;
}