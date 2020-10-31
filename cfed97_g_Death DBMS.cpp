#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;
const int N=1e6+10;
int n,m;
int trie[N][26],total,fail[N],last[N];
int id[N],node_no[N],val[N]; //val:保存每个字符串的值，用于从multiset中反找

char s[N];
multiset<int> ss[N];//下标索引为id

void insert(char *s,int num)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        if(!trie[u][x]) trie[u][x]=++total;
        u=trie[u][x];
    }
    if(!id[u]) id[u]=num;
    node_no[num]=u;
    ss[id[u]].insert(0);
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
                last[trie[u][i]]=(id[fail[trie[u][i]]]==0)?(last[fail[trie[u][i]]]):(fail[trie[u][i]]); //有效字符串结尾
                q.push(trie[u][i]);
            }
            else
            {
                trie[u][i]=trie[fail[u]][i];
            }
        }
    }

}

int get_val(int u)
{
    //return val[id[u]];
    return *(--ss[id[u]].end());
}

void modify_val(int i,int x)
{
    //val[id[node_no[i]]]=x;
    ss[id[node_no[i]]].erase(ss[id[node_no[i]]].find(val[i]));
    ss[id[node_no[i]]].insert(x);
    val[i]=x;
}

int query(char *s)
{
    int ans=-1,u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        u=trie[u][x];
        for(int j=u;j;j=last[j])
        {
            if(id[j])
                ans=max(ans,get_val(j));
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>s+1;
        insert(s,i);
    }
    build();
    for(int i=1;i<=m;i++)
    {
        int op,x,y;
        cin>>op;
        if(op==1)
        {
            cin>>x>>y;
            modify_val(x,y);
        }
        else
        {
            cin>>s+1;
            cout<<query(s)<<endl;
        }
    }

    return 0;
}