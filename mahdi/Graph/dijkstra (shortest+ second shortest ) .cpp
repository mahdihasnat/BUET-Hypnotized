vector<pair<int, int> > adj[N]; /// vertex , weight
int d[N];
int d2[N];
int p[N];
int n;
void dijkstra(int s)
{
    memset(d,0x3f3f3f3f,sizeof d);
    memset(d2,0x3f3f3f3f,sizeof d2);
    d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty())
    {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;
        for (auto edge : adj[v])
        {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to])
            {

                d2[to] = d[to];
                d[to] = d[v] + len;
                q.push({d[to], to});


            }
            else if(d[v]+ len > d[to] && d[v]+len  < d2[to])
            {
                d2[to] = d[v] + len;
                q.push({d[to],to});


            }
            if(d2[v]+ len < d2[to])
            {
                d2[to] = d2[v] + len;
                q.push({d[to],to});
            }
        }
    }
}
