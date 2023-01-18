struct hackenbush {
 int n;
 vector<vector<int>> adj;
 hackenbush(int n) : n(n), adj(n) { }
 void add_edge(int u, int v) {
  adj[u].push_back(v);
  if (u != v) adj[v].push_back(u);
 }
 // r is the only root connecting to the ground
 int grundy(int r) {
  vector<int> num(n), low(n);
  int t = 0;
  function<int(int, int)> dfs = [&](int p, int u) {
   num[u] = low[u] = ++t;
   int ans = 0;
   for (int v : adj[u]) {
    if (v == p) { p += 2 * n; continue; }
    if (num[v] == 0) {
     int res = dfs(u, v);
     low[u] = min(low[u], low[v]);
     if (low[v] > num[u]) ans ^= (1 + res) ^ 1; // bridge
     else  ans ^= res;  // non bridge
    } else low[u] = min(low[u], num[v]);
   }
   if (p > n) p -= 2 * n;
   for (int v : adj[u])
    if (v != p && num[u] <= num[v]) ans ^= 1;
   return ans;
  };
  return dfs(-1, r);
 }
};
int main() {
 int cases; scanf("%d", &cases);
 for (int icase = 0; icase < cases; ++icase) {
  int n; scanf("%d", &n);
  vector<int> ground(n);
  int r;
  for (int i = 0; i < n; ++i) {
   scanf("%d", &ground[i]);
   if (ground[i] == 1) r = i;
  }
  int ans = 0;
  hackenbush g(n);
  for (int i = 0; i < n - 1; ++i) {
   int u, v;
   scanf("%d %d", &u, &v);
   --u; --v;
   if (ground[u]) u = r;
   if (ground[v]) v = r;
   if (u == v) ans ^= 1;
   else g.add_edge(u, v);
  }
  int res = ans ^ g.grundy(r);
  printf("%d\n", res != 0);
 }
}