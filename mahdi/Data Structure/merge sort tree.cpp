const int N=5e5+5;
const int oo=1e9+7;
vector< pii  > value[4*N];
int a[N];

void merge(const vector<pii> &a, const vector<pii> &b, vector<pii > &res)  // wrong algo
{
    res.clear();
    int j=0;
    for(int i=0; i<a.size(); i++)
    {
        while(j<b.size() && b[j].first < a[i].first)
        {
            res.push_back(b[j++]);
        }
        if(j<b.size() && b[j].first == a[i].first)
            res.push_back({a[i].first,a[i].second+b[j++].second});
        else
            res.push_back(a[i]);
    }
    while(j<b.size())
        res.push_back(b[j++]);
}

void UpdatePoint(int node, int ss, int se, int u, int x)
{
    int mid = ss+(se-ss)/2;

    if (ss>se || ss>u || se<u)
        return ;

    if (ss==se&& ss==u)
    {
        value[node][0].first=x;
        return;
    }

    UpdatePoint(2*node, ss, mid, u, x);
    UpdatePoint(2*node+1, mid+1, se, u, x);
    merge(value[2*node],value[2*node+1],value[node]);

}
vector<pii>  GetSum(int node,int ss, int se, int qs, int qe)
{
    int mid = ss+(se-ss)/2;

    if (ss>se || ss>qe || se<qs)
        return vector<pii>(0);

    if (ss>=qs && se<=qe)
        return value[node];
    vector<pii> x;
    merge(GetSum(2*node,ss,mid,qs,qe),GetSum(2*node+1,mid+1,se,qs,qe),x);
    return x;
}

void Build(int node,int *a,int ss,int se)
{
    if(ss==se)
    {
        value[node].push_back({a[ss],1});
        return ;
    }
    int mid = ss+(se-ss)/2;
    Build(2*node,a,ss,mid);
    Build(2*node+1,a,mid+1,se);
    merge(value[2*node],value[2*node+1],value[node]);
}
