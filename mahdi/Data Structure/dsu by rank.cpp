
int parent[N];
int rnk[N];
int find_set(int v)
{
    return parent[v] == v ? v :  parent[v] = find_set(parent[v]);
}

void make_set(int v)
{
    parent[v] = v;
    rnk[v] = 0;
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}
