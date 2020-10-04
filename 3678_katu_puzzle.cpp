#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int N=4010,M=2e6+5;
struct E
{
    int to,inext;
}edge[M];//edge_c[M];
int head[N],total;//head_c[N],total_c;
int dfn[N],low[N],dfn_cnt;
int st[N],st_p,scc_cnt,c[N]; //stack, scc_count
bool inst[N]; //in stack

int n,m;

void adde(int x,int y)
{
    edge[++total].to=y;
    edge[total].inext=head[x];
    head[x]=total; //!
}

/*void adde_c(int x,int y)
{
    edge_c[++total_c].to=y;
    edge_c[total_c].inext=head_c[x];
    head_c[x]=total_c;
}*/

set<int> s;
bool flag=true;
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
            if(!flag) return ;
            low[x]=min(low[x],low[y]);
        }
        else if(inst[y])
            low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) //scc
    {
        scc_cnt++;
        int y;
        s.clear(); //没必要用set，可用c[i]==c[i+n]以On时间判断合法性
        do
        {
            y=st[st_p--]; //!
            inst[y]=false;
            c[y]=scc_cnt;
            if(y>n && s.find(y-n)!=s.end()) flag=false;
            if(y<=n && s.find(y+n)!=s.end()) flag=false;
            s.insert(y);
        } while (x!=y);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m; //1~n,n+1~2*n
    for(int i=1;i<=m;i++)
    {
        int aa,bb,cc;
        char op[10];
        cin>>aa>>bb>>cc>>op;
        aa++;
        bb++;
        if(op[0]=='A')
        {
            if(cc==0)
            {
                adde(aa+n,bb);
                adde(bb+n,aa);
            }
            else if(cc==1)
            {
                adde(aa,aa+n);
                adde(bb,bb+n);
            }
        }
        else if(op[0]=='O')
        {
            if(cc==0)
            {
                adde(aa+n,aa);
                adde(bb+n,bb);
            }
            else if(cc==1)
            {
                adde(aa,bb+n);
                adde(bb,aa+n);
            }
        }
        else if(op[0]=='X')
        {
            if(cc==0)
            {
                adde(aa,bb),adde(bb,aa);
                adde(aa+n,bb+n),adde(bb+n,aa+n);
            }
            else if(cc==1)
            {
                adde(aa,bb+n),adde(bb,aa+n);
                adde(aa+n,bb),adde(bb+n,aa);
            }
        }
    }
    for(int i=1;i<=n*2;i++)
    {
        if(!dfn[i]) tarjan(i);
        if(!flag) break;
    }
    if(!flag)
        cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}