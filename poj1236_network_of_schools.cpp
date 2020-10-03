#include <iostream>
using namespace std;
const int N=110,M=10100;
struct E
{
    int to,inext;
}edge[M],edge_c[M];
int head[N],total;
int head_c[N],total_c;
int n;
int dfn[N],low[N],dfn_cnt;
int c[N],cnt,st[N],st_p;
bool inst[N];
int in_degree[N],out_degree[N];

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
    if(dfn[x]==low[x])
    {
        cnt++;
        while (st[st_p]!=x)
        {
            int y=st[st_p];
            inst[y]=false;
            c[y]=cnt;
            st_p--;
        }
        //x
        inst[x]=false;
        c[x]=cnt;
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
            if(c[i]==c[y]) continue;
            adde_c(c[i],c[y]);
            in_degree[c[y]]++;
            out_degree[c[i]]++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int y;
        while (true)
        {
            cin>>y;
            if(!y) break;
            adde(i,y);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    create_new_graph();
    int zero_in_cnt=0,zero_out_cnt=0;
    for(int i=1;i<=cnt;i++) //!!
    {
        if(!in_degree[i]) zero_in_cnt++;
        if(!out_degree[i]) zero_out_cnt++;
    }
    //ans1
    cout<<zero_in_cnt<<endl;
    //ans2
    if(cnt==1)
        cout<<0<<endl;
    else cout<<max(zero_in_cnt,zero_out_cnt)<<endl;

    return 0;
}