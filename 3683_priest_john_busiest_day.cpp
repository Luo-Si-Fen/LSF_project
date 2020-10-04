#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N=2010,M=3e6+10;
struct E
{
    int from,to,inext;
}edge[M],edge_c[M];
int head[N],head_c[N],total,total_c;
int dfn[N],low[N],dfn_cnt;
int st[N],st_p,scc_cnt,c[N]; //stack, scc_count
bool inst[N]; //in stack
int in_degree[N];
int val[N], opp[N]; //constructed value, opposite point of scc

int n;
struct D
{
    int st,ed,d;
}ti[N];

void adde(int x,int y)
{
    edge[++total].to=y;
    edge[total].from=x;
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

bool overlap(int a,int b,int c,int d)
{
    if(a>c)
    {
        swap(a,c);
        swap(b,d);
    }
    //a<=c
    if(b>c) return true;
    return false;
}

void create_new_graph() // 反图
{
    for(int i=1;i<=total;i++)
    {
        int x=edge[i].from,y=edge[i].to;
        if(c[x]!=c[y])
        {
            adde_c(c[y],c[x]);
            in_degree[c[x]]++;
        }
    }
}

void topo()
{
    queue<int> q;
    for(int i=1;i<=scc_cnt;i++)
        if(in_degree[i]==0) q.push(i);
    while (q.size())
    {
        int x=q.front();
        q.pop();
        if(val[x]==-1) val[x]=0,val[opp[x]]=1;
        for(int e=head_c[x];e;e=edge_c[e].inext)
        {
            int y=edge_c[e].to;
            in_degree[y]--;
            if(in_degree[y]==0) q.push(y);
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int h1,m1,h2,m2,d;
        scanf("%d:%d %d:%d %d",&h1,&m1,&h2,&m2,&d);
        ti[i].st=h1*60+m1;
        ti[i].ed=h2*60+m2;
        ti[i].d=d;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            //0-0
            if(overlap(ti[i].st,ti[i].st+ti[i].d,ti[j].st,ti[j].st+ti[j].d))
                adde(i,n+j),adde(j,n+i);
            //0-1
            if(overlap(ti[i].st,ti[i].st+ti[i].d,ti[j].ed-ti[j].d,ti[j].ed))
                adde(i,j),adde(j+n,i+n);
            //1-0
            if(overlap(ti[i].ed-ti[i].d,ti[i].ed,ti[j].st,ti[j].st+ti[j].d))
                adde(i+n,j+n),adde(j,i);
            //1-1
            if(overlap(ti[i].ed-ti[i].d,ti[i].ed,ti[j].ed-ti[j].d,ti[j].ed))
                adde(i+n,j),adde(j+n,i);
        }
    }
    for(int i=1;i<=2*n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    bool flag=true;
    for(int i=1;i<=n;i++)
    {
        if(c[i]==c[i+n])
        {
            flag=false;
            break;
        }
        opp[c[i]]=c[i+n]; opp[c[i+n]]=c[i];
    }
    if(!flag) puts("NO");
    else
    {
        puts("YES");
        create_new_graph();
        memset(val,-1,sizeof(val));
        topo();
        for(int i=1;i<=n;i++)
        {
            if(val[c[i]]==0) //begin
            {
                printf("%02d:%02d %02d:%02d\n",ti[i].st/60,ti[i].st%60,(ti[i].st+ti[i].d)/60,(ti[i].st+ti[i].d)%60);
            }
            else //end
            {
                printf("%02d:%02d %02d:%02d\n",(ti[i].ed-ti[i].d)/60,(ti[i].ed-ti[i].d)%60,(ti[i].ed)/60,(ti[i].ed)%60);
            }
        }
    }
    
    return 0;
}