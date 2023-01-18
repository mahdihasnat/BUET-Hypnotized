/*
    Complexity = O(V^2 E)
    clear() -> clear flow value of existing graph
*/


#define FlowType int
const FlowType flow_oo = 1e9;
struct FlowEdge
{
    int u,v;
    FlowType cap, flow;
    FlowEdge(int u,int v,FlowType cap):u(u), v(v),cap(cap), flow(0) {}
};

struct Dinic
{
    vector<FlowEdge > edges;
    vector< vector<int > > adj;
    vector<int > label , pt;

    Dinic(int n):adj(n),label(n) , pt(n)  {}


    int AddEdge(int u,int v,FlowType cap)
    {
        adj[u].emplace_back(edges.size());
        edges.emplace_back(u,v,cap);

        adj[v].emplace_back(edges.size());
        edges.emplace_back(v,u,0);

        return edges.size() - 2;
    }

    bool bfs(int s,int t)
    {
        fill(label.begin() , label.end() , -1 );

        label[s] = 0;
        queue<int > q;
        q.emplace(s);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for(int i: adj[u])
            {
                FlowEdge &e = edges[i];
                if(label[e.v] == -1 and e.flow < e.cap )
                {
                    label[e.v] = label[u]+1;
                    q.emplace(e.v);
                }
            }
        }
        return label[t]!=-1;
    }
    FlowType dfs(int s,int t,FlowType pushed)
    {
        if(s==t or pushed == 0) return pushed;
        FlowType flow = 0 , newflow ;
        for(int &i = pt[s] ; i< adj[s].size();i++)
        {
            FlowEdge &e = edges[adj[s][i]] ;
            if(label[e.v] == label[s]+1  and (newflow = dfs(e.v , t , min(pushed , e.cap - e.flow))) > 0 )
            {
                e.flow+=newflow;
                edges[adj[s][i]^1].flow-=newflow;

                flow+=newflow;
                pushed-=newflow;

                if(pushed == 0) break;
            }
        }
        return flow;
    }

    FlowType maxflow(int s,int t)
    {
        FlowType flow = 0;
        while(bfs(s,t))
        {
            fill(pt.begin() , pt.end() , 0);
            flow+=dfs(s,t,flow_oo);
        }
        return flow;
    }
    void clear()
    {
        for(FlowEdge &e : edges)
            e.flow = 0;
    }
    void print()
    {
        for(int i=0; i<adj.size(); i++)
        {
            cerr<<i<<": ";
            for(int j : adj[i])
                cerr<<" "<<edges[j].v<<"("<<edges[j].flow<<"/"<<edges[j].cap<<")";
            cerr<<endl;
        }
    }
};
