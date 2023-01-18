vector<pair<int, int> > adj[N];
int d[N];
int cnt[N];
bool inqueue[N];
int n;
bool spfa(int s ) {

    memset(d,0x3f3f3f3f,sizeof d);
    memset(cnt,0,sizeof cnt);
    memset(inqueue,0,sizeof inqueue);

    queue<int> q;

    d[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        inqueue[v] = false;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                if (!inqueue[to]) {
                    q.push(to);
                    inqueue[to] = true;
                    cnt[to]++;
                    if (cnt[to] > n)
                        return false;  // negative cycle
                }
            }
        }
    }
}
