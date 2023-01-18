/*
    Complexity = O(V E^2)
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

struct EdmondsKarp
{
    vector<FlowEdge > edges;
    vector< vector<int > > adj;
    vector<int > parentEdge;

    EdmondsKarp(int n):adj(n),   parentEdge(n)  {}


    int AddEdge(int u,int v,FlowType cap)
    {
        adj[u].emplace_back(edges.size());
        edges.emplace_back(u,v,cap);

        adj[v].emplace_back(edges.size());
        edges.emplace_back(v,u,0);

        return edges.size() - 2;
    }

    FlowType bfs(int s,int t)
    {
        fill(parentEdge.begin(), parentEdge.end(), -1 );
        parentEdge[s] = -2;

        queue<pair<int, FlowType >  > q;
        q.push({s,flow_oo});

        while(!q.empty())
        {
            int u = q.front().first;
            FlowType flow = q.front().second;


            q.pop();

            for(int i: adj[u])
            {
                FlowEdge &e = edges[i];
                FlowType newflow = min(flow, e.cap - e.flow);
                if(parentEdge[e.v] == -1 and newflow > 0 )
                {
                    parentEdge[e.v] = i ;
                    if(e.v == t)    return newflow;
                    q.push({e.v, newflow});
                }
            }
        }
        return 0;
    }
    FlowType maxflow(int s,int t)
    {
        FlowType flow = 0, newflow;
        while((newflow = bfs(s,t)))
        {
            int v = t;
            while(parentEdge[v]!=-2)
            {

                edges[parentEdge[v]].flow+=newflow;
                edges[parentEdge[v]^1].flow-=newflow;
                v=edges[parentEdge[v]].u;
            }
            flow+=newflow;
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
