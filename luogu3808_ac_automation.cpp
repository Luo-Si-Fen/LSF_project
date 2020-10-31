#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N=3e6+10;
int n,m;
int trie[N][26],total,fail[N];
int ed[N];

char s[N];

void insert(char *s,int num)
{
    int u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        if(!trie[u][x]) trie[u][x]=++total;
        u=trie[u][x];
    }
    ed[u]++;
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

}

int query(char *s)
{
    int ans=0,u=0;
    for(int i=1;s[i];i++)
    {
        int x=s[i]-'a';
        u=trie[u][x];
        for(int j=u;j && ed[j]!=-1;j=fail[j])
        {
            ans+=ed[j];
            ed[j]=-1;
        }
    }
    return ans;
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
    cin>>s+1;
    cout<<query(s)<<endl;
    return 0;
}