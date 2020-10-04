#include<bits/stdc++.h>
using namespace std;
const int Max=5007;
int n,m,p;
int fa[Max];
void Init(int size)
{
    for(int i=1;i<=size;i++)
        fa[i]=i;
}
int find_father(int x)
{
    return (fa[x]==x)?x:(fa[x]=find_father(fa[x]));
}
inline void _union(int x,int y)
{
	int fa_x=find_father(x); //找到x和y的帮主
    int fa_y=find_father(y);
    if(fa_x!=fa_y)   //如果不是同一个人的话，就合并
    	fa[fa_x]=fa_y;
}
int main()
{
    cin>>n>>m>>p;
    Init(n);
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        if(find_father(a)!=find_father(b))_union(a,b);
    }
    for(int i=1;i<=p;i++)
    {
        int a,b;
        cin>>a>>b;
        cout<<((find_father(a)==find_father(b))?"Yes":"No")<<endl;
    }
}
