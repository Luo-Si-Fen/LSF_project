#include <iostream>
#include <cstdio>
#include <memory.h>
#include <queue>
using namespace std;
const int N=1e6+10;
int n;
char s[151][100],t[N];
int trie[N][26],total,id[N],fail[N],last[N];
int cnt[N];

void insert(char *s,int num)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        if(!trie[u][x]) trie[u][x]=++total;
        u=trie[u][x];
    }
    id[u]=num;
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
            else trie[u][i]=trie[fail[u]][i];
        }
    }
}

void query(char *s)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        u=trie[u][x];
        for(int j=u;j;j=last[j])
        {
            cnt[id[j]]++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    while (cin>>n && n)
    {
        memset(trie,0,sizeof(trie));
        memset(fail,0,sizeof(fail));
        memset(last,0,sizeof(last));
        memset(cnt,0,sizeof(cnt));
        memset(id,0,sizeof(id));
        for(int i=1;i<=n;i++)
        {
            cin>>s[i]+1;
            insert(s[i],i);
        }
        build();
        cin>>t+1;
        query(t);
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            ans=max(ans,cnt[i]);
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;i++)
            if(ans==cnt[i]) cout<<s[i]+1<<endl;
    }
    
    return 0;
}