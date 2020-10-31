//二次加强版
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N=2e5+1,M=2e6+10;
int n;
char s[N],t[M];
int trie[M/2][26],total,fail[M/2];
int id[M/2],node_[N]; //结点和字符串编号的映射
int delta[M/2],sum[M/2];//树上差分数组，差分求和

struct E
{
    int to,inext;
}edge[M/2];
int head[M/2],e_total;

void adde(int x,int y)
{
    edge[++e_total].to=y;
    edge[e_total].inext=head[x];
    head[x]=e_total;
}

void insert(char *s,int num)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        if(!trie[u][x]) trie[u][x]=++total; //!!
        u=trie[u][x];
    }
    if(!id[u]) id[u]=num;
    node_[num]=u;
}

void build()
{
    queue<int> q;
    for(int i=0;i<26;i++)
    {
        if(trie[0][i]) q.push(trie[0][i]);
    }
    while (q.size())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(trie[u][i])
            {
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
            else
            {
                trie[u][i]=trie[fail[u]][i];
            }
        }
    }
    for(int i=1;i<=total;i++)
    {
        adde(fail[i],i);
    }
}

void traverse(char *s)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        u=trie[u][x];
        delta[u]++;
    }
}

void dfs(int u=0)
{
    sum[u]=delta[u];
    for(int e=head[u];e;e=edge[e].inext)
    {
        int y=edge[e].to;
        dfs(y);
        sum[u]+=sum[y];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s+1;
        insert(s,i);
    }
    build();
    cin>>t+1;
    traverse(t);
    dfs(0);
    for(int i=1;i<=n;i++)
    {
        cout<<sum[node_[i]]<<endl;
    }
    return 0;
}