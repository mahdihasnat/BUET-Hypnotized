int parent[N];
int size[N];

stack < pair<int, int  > > added;

void make_set(int v)
{
    parent[v] = v;
    size[v] = 1;
}

inline int find_set(int u)
{
    return parent[u]==u ? u : find_set(parent[u]);
}
inline void rollback()
{
    assert(added.size()>=1);

    auto top= added.top();
    added.pop();

    if(top.first!=top.second)
    {
        size[top.second]-=size[top.first];
        parent[top.first] = top.first;
    }
}

inline void union_sets(int u,int v)
{
    u=find_set(u) ;
    v =find_set(v);

    if(u==v)
    {
        added.push({u,v});
        return ;
    }
    if(size[u]>size[v])
    {
        swap(u,v);
    }
    /// now u < v by size


    size[v]+=size[u];
    parent[u]=v;
    added.push({u,v});

}
