#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N=2e4+5,M=2e5+5;
struct E
{
    int to,inext;
}edge[M],edge_c[M];
int head[N],total;
int head_c[N],total_c;
int n,m,a[N];
//vector<int> scc[N];
int st[N],st_p,cnt,c[N],sum[N]; //stack, scc_count, scc_sum
int dfn[N],low[N],dfn_cnt;
bool inst[N]; //in stack
int in_degree[N];

void adde(int x,int y)
{
    edge[++total].to=y;
    edge[total].inext=head[x];
    head[x]=total;
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
    st[++st_p]=x; inst[x]=true;
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
    if(dfn[x]==low[x]) //scc judge success
    {
        cnt++;
        while (st[st_p]!=x)
        {
            int y=st[st_p];
            //scc[cnt].emplace_back(y);
            inst[y]=false;
            c[y]=cnt;
            sum[cnt]+=a[y];
            st_p--;
        }
        //x
        //scc[cnt].emplace_back(x);
        inst[x]=false;
        c[x]=cnt;
        sum[cnt]+=a[x];
        st_p--;
    }
}

void create_new_graph()
{
    for(int i=1;i<=n;i++)
    {
        for(int e=head[i];e;e=edge[e].inext)
        {
            int y=edge[e].to;
            if(c[i]==c[y]) continue; //same scc
            else 
            {
                adde_c(c[i],c[y]);
                in_degree[c[y]]++;
            }
        }
    }
}

int f[N],ans=0;
void topo() //for Graph2
{
    queue<int> q;
    for(int i=1;i<=cnt;i++)
    {
        if(!in_degree[i])
        {
            q.push(i);
            f[i]=sum[i];
            ans=max(ans,f[i]);
        }
    }

    while (q.size())
    {
        int x=q.front();
        q.pop();

        for(int e=head_c[x];e;e=edge_c[e].inext)
        {
            int y=edge_c[e].to;
            f[y]=max(f[y],f[x]+sum[y]);
            ans=max(ans,f[y]);
            in_degree[y]--;
            if(!in_degree[y])
                q.push(y);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        adde(x,y);
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    create_new_graph();
    topo();
    cout<<ans<<endl;
    return 0;
}