
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;


#define ALL(a) a.begin(), a.end()

const int N=10000+5;
const int oo=1e9+7;



int n; // number of nodes
vector<int> adj[N]; // adjacency list of graph

bool visited[N];
int tin[N];
int low[N];
int timer;
vector<pii> ans;
void IS_BRIDGE(int u,int v)
{
    if(v<u) swap(u,v);
    ans.push_back({u,v});
}
void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}

void find_bridges() {
    timer = 0;
    memset(visited,0,sizeof visited);
    memset(tin,-1,sizeof tin);
    memset(low,-1,sizeof low);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
int32_t main()
{

    int T,cs=0;
    scanf("%d",&T);
    while(T--)
    {
        printf("Case %d:\n",++cs);

        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            int u,k;
            scanf("%d (%d)",&u,&k);
            while(k--)
            {
                int a;
                scanf("%d",&a);
                adj[u].push_back(a);

            }

        }
        find_bridges();
        sort(ALL(ans));
        printf("%d critical links\n",ans.size());
        for(int i=0;i<ans.size();i++)
        {
            printf("%d - %d\n",ans[i].first,ans[i].second);
        }
        ans.clear();
        for(int i=0;i<n;i++) adj[i].clear();
    }
}
