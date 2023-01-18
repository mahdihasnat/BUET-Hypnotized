class CentroidDecomposition{
public:
 vector<vector<int> >adj;
 vector<int>sz,parent;
 vector<bool>vis;
 int n,root;
 CentroidDecomposition(vector<vector<int> >&a) {
  adj = a; n = adj.size(); sz.resize(n); parent.resize(n,-1);
  vis.resize(n,false);
  build(0,-1);
 }
 void build(int s, int p) {
  dfs(s,p);
  int c= centroid(s,p,sz[s]); vis[c]= true;
  if(p!=-1) { parent[c] = p; }
  else { root = c; }
  for(auto it:adj[c]) { if(vis[it]) continue;
   build(it,c);
  }
 }
 void dfs(int s, int p) {
  sz[s] = 1;
  for(auto i:adj[s]) { if(i==p || vis[i]) continue;
   dfs(i,s); sz[s]+= sz[i];
  }
 }
 int centroid(int s,int  p, int total) {
  for(auto i:adj[s]) { if(i==p || vis[i]) continue;
   if(sz[i]*2>total) return centroid(i,s,total);
  }
  return s;
 }
};
