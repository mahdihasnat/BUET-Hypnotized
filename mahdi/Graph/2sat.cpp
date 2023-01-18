vector<int> g[N], gt[N];
bool used[N];
bool assignment[N];
vector<int> order;
int comp[N];

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT(int n) /// 2 * number of variable
 {
    order.clear();
    memset(used ,  0  ,sizeof used);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    memset(comp ,  -1  ,sizeof comp);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;

        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}
void add(int u , int v)
{
    g[u].emplace_back(v);
    gt[v].emplace_back(u);
}
