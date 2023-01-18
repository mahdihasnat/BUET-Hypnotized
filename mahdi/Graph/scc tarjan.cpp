stack<int> st;
vector<vector<int> > scc; /// contains the node's of i'th scc , 0 indexed
int low[N], disc[N], scc_id[N];
int dfs_time;
bool in_stack[N];

vector<int >  g[N]; /// input graph
vector<int > g_condensation[N]; /// output graph ( contains edges of condensation graph)
void dfs(int u)
{
	low[u] = dfs_time;
	disc[u] = dfs_time;
	dfs_time++;

	in_stack[u] = true;
	st.push(u);

	for(int v: g[u])
	{
		if(disc[v] == -1)
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(in_stack[v] == true)
			low[u] = min(low[u], disc[v]);
	}

	if(low[u] == disc[u])
	{
		scc.push_back(vector<int>());
		while(st.top() != u)
		{
			scc.back().push_back(st.top());
			in_stack[st.top()] = false;
			scc_id[st.top()] = scc.size()-1;
			st.pop();
		}

		scc.back().push_back(u);
		in_stack[u] = false;
		scc_id[u] = scc.size()-1;
		st.pop();
	}
}

int tarjan(int n)
{
	memset(scc_id, -1, sizeof(scc_id));
	memset(disc, -1, sizeof(disc));
	memset(low, -1, sizeof(low));
	memset(in_stack, 0, sizeof(in_stack));
	dfs_time = 0;

    while(!st.empty()) st.pop();
    scc.clear();

	for(int i = 1; i <= n; i++)
		if(disc[i] == -1)
			dfs(i);

    for(int i=1;i<=n;i++)
    {
        for(int j: g[i])
            if(scc_id[i]!=scc_id[j])
                g_condensation[scc_id[i]].push_back(scc_id[j]);
    }

	return scc.size();
}
