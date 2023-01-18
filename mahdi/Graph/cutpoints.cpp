
#include <bits/stdc++.h>
using namespace std;



const int N=10000+5;
const int oo=1e9+7;


int n; // number of nodes
vector<int> adj[N]; // adjacency list of graph

bool visited[N];
int tin[N];
int low[N];
int timer;

bool iscutpoint[N];
void IS_CUTPOINT(int u)
{
    iscutpoint[u]=1;
}

void dfs(int v, int p = -1)
{
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v])
    {
        if (to == p)
            continue;
        if (visited[to])
        {
            low[v] = min(low[v], tin[to]);
        }
        else
        {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints()
{
    timer = 0;
    memset(visited,0,sizeof visited);
    memset(tin,-1,sizeof tin);
    memset(low,-1,sizeof low);
    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
            dfs (i);
    }
}
int32_t main()
{

    int T,cs=0;
    scanf("%d",&T);
    while(T--)
    {
        printf("Case %d: ",++cs);

        int m;
        scanf("%d %d",&n,&m);
        while(m--)
        {
            int u,k;
            scanf("%d %d",&u,&k);
            u--,k--;
            adj[u].push_back(k);
            adj[k].push_back(u);

        }
        int ans=0;
        memset(iscutpoint,0,sizeof iscutpoint);
        find_cutpoints();
        for(int i=0;i<n;i++) ans+=iscutpoint[i];
        printf("%d\n",ans);
        for(int i=0; i<n; i++)
            adj[i].clear();
    }
}
