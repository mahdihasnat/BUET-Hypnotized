const long long flow_inf = 1e18;
struct FlowEdge {
  int v,u,id; long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap,int id=-1) : v(v), u(u), cap(cap),id(id) {}
};
struct Dinic
{
  vector<FlowEdge> edges; vector<vector<int> > adj;
  int n, m = 0; int s, t;
  vector<int> level, ptr,flow_through;
  queue<int> q; vector<bool>vis;
  int maxid=0;
  Dinic() {}
  Dinic(int n) : n(n) {
    vis.resize(n); adj.resize(n);
    level.resize(n); ptr.resize(n);
  }
  void add_edge(int v, int u, long long cap,int id=-1) {
    edges.emplace_back(v, u, cap,id);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
    if(id!=-1)maxid++;
  }
  void dfs2(int s) {
    vis[s] = 1;
    for(int i:adj[s]) {
      int id = i; int u = edges[id].v;
      int v = edges[id].u;
      if(edges[id].flow!=edges[id].cap && !vis[v])
      {
        dfs2(v);
      }
    }
  }
  vector<int> getMinCut() {
    dfs2(s); vector<int>ret;
    for(int i=0; i<n; i++) {
      if(vis[i]) ret.push_back(i);
    }
    return ret;
  }
  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v])
      {
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }
  long long dfs(int v, long long pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++){
      int id = adj[v][cid]; int u = edges[id].u;
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr; edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }
  long long flow(int _s,int _t) {
    s=_s; t=_t;
    long long f = 0;
    while (true)
    {
      fill(level.begin(), level.end(), -1);
      level[s] = 0; q.push(s);
      if (!bfs()) break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)){
        f += pushed;
      }
    }
    flow_through.assign(maxid+1, 0);
    for(int i = 0; i < n; i++){
      for(auto j : adj[i]) {
        int idx = j;
        FlowEdge e = edges[idx];
        if(e.id >= 0)flow_through[e.id] = e.flow;
      }
    }
    return f;
  }
};

/*for bipartite graph*/
class Minimum_node_cover
{
public:
  map<pair<int,int>,bool>matched;
  vector<vector<int> >adj;
  vector<int>minimum_vertex,maximum_set,l,r;
  vector<bool>vis;
  /*number of nodes in dinic without source and destination src = 0 ,dest = sz+1
d.flow() should be called before constructor calling*/
  Minimum_node_cover(int sz, Dinic &d){
    adj.resize(sz+5);vis.resize(sz+5);
    for(auto it:d.edges){
      if(it.u>0 && it.u <=sz && it.v>0 && it.v<=sz && it.cap==1){
        if(it.flow==1){
          adj[it.u].push_back(it.v);
          matched[ {it.u,it.v}]=1;
        }
        else adj[it.v].push_back(it.u);
      }
    }
    for(auto it:d.edges){
      if(it.v==0 && it.cap==1) l.push_back(it.u);
      if(it.u==sz+1 && it.cap==1) r.push_back(it.v);
    }
    sort(l.begin(),l.end());sort(r.begin(),r.end());
    l.resize(distance(l.begin(),unique(l.begin(),l.end())) );
    r.resize(distance(r.begin(),unique(r.begin(),r.end())) );
    for(auto it:d.edges){
      if(it.v==0 && it.cap==1 && it.flow==0){
        if(!vis[it.u]) dfs2(it.u, 1);
      }
    }
    for(int i:l){
      if(!vis[i]) minimum_vertex.push_back(i);
      else maximum_set.push_back(i);
    }
    for(int i:r){
      if(vis[i]) minimum_vertex.push_back(i);
      else maximum_set.push_back(i);
    }
  }
  void dfs2(int s, bool bam){
    vis[s] = 1;
    if(bam){
      for(int i:adj[s]){
        if(vis[i]) continue;
        if(matched[ {s,i}]==0) dfs2(i,0);
      }
    }
    else{
      for(int i:adj[s]){
        if(vis[i]) continue;
        if(matched[{s,i}]==1) dfs2(i,1);
      }
    }
  }
};
//flow_through[i] = extra flow beyond 'low' sent through edge i
struct LR_Flow{
  Dinic F;int n, s, t;
  struct edge{
    int u, v, l, r, id;
  };
  vector<edge> edges;
  LR_Flow() {}
  LR_Flow(int _n){
    n = _n + 2;s = n - 2, t = n - 1;;
    edges.clear();
  }
  void add_edge(int u, int v, int l, int r, int id = -1){
    assert(0 <= l && l <= r);
    edges.push_back({u, v, l, r, id});
  }
  bool feasible(int _s = -1, int _t = -1, int L = -1, int R = -1)
  {
    if (L != -1)
      edges.push_back({_t, _s, L, R, -1});
    F = Dinic(n);
    long long target = 0;
    for (auto e : edges){
      int u = e.u, v = e.v, l = e.l, r = e.r, id = e.id;
      if (l != 0){
        F.add_edge(s, v, l);F.add_edge(u, t, l);
        target += l;
      }
      F.add_edge(u, v, r - l, id);
    }
    auto ans = F.flow(s, t);
    if (L != -1)edges.pop_back();
    if (ans < target)return 0; //not feasible
    return 1;
  }
  int max_flow(int _s, int _t){   //-1 means flow is not feasible
    int mx = 1e5 + 9;
    if (!feasible(_s, _t, 0, mx))return -1;
    return F.flow(_s, _t);
  }
  int min_flow(int _s, int _t){   //-1 means flow is not feasible
    int mx = 1e9;int ans = -1, l = 0, r = mx;
    while (l <= r){
      int mid = l + r >> 1;
      if (feasible(_s, _t, 0, mid))
        ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    return ans;
  }
};