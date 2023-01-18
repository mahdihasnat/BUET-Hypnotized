// tested on LOJ-1308 Ant Network
struct BlockCutTree
{
	vector<int> g[N];// input graph
	vector<int> g2[N]; // output graph
	int sz_tree=0;
	vector<int> comp[N]; // nodes that belong i'th blocks without bridge vertex
	int to_comp[N];
	bool is_bridge[N];
	int tin[N];
	int low[N];
	int timer=1;
	void dfs_bridge(int u,int p=-1)
	{
		tin[u]=low[u]=timer++;
		is_bridge[u]=0;
		int child=0;
		for(int v: g[u])
		{
			if(v==p) continue;
			if(tin[v]==-1)
			{
				child++;
				dfs_bridge(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v] >= tin[u] and p!=-1)
				{
					is_bridge[u]=1;
				}
			}
			else low[u]=min(low[u],tin[v]);
		}
		if(p==-1 and child >1)
			is_bridge[u]=1;
	}

	void add_component(int u,int cid)
	{
		to_comp[u]=cid;
		comp[cid].push_back(u);

		if(is_bridge[u]) return;

		for(int v: g[u])
		{
			if(is_bridge[v]) continue;
			if(to_comp[v]==-1)
			{
				add_component(v,cid);
			}
		}
	}

	void decompose(int n)
	{
		memset(tin,-1,sizeof(tin[0])*(n+1));
		timer=1;
		for(int i=1;i<=n;i++)
		{
			if(tin[i]==-1)
			{
				dfs_bridge(i);
			}
		}

		memset(to_comp,-1,sizeof(to_comp[0])*(n+1));
		sz_tree=0;
		for(int i=1;i<=n;i++)
		{
			if(to_comp[i]==-1)
			{
				comp[sz_tree].clear();
				add_component(i,sz_tree++);
			}
		}
		// DBG(sz_tree);
		for(int i=0;i<sz_tree;i++) g2[i].clear();
		for(int u=1;u<=n;u++)
		{
			assert(to_comp[u]!=-1);
			for(int v: g[u])
			{
				assert(to_comp[v]!=-1);
				if(to_comp[u]!=to_comp[v])
				{
					g2[to_comp[u]].push_back(to_comp[v]);
					g2[to_comp[v]].push_back(to_comp[u]);
				}
			}
		}
		for(int i=0;i<sz_tree;i++)
			sort(ALL(g2[i])),g2[i].erase(unique(ALL(g2[i])),g2[i].end());
	}
};
