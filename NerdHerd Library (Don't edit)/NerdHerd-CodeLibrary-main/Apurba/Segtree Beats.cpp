struct info
{
    int maxi = 0,smaxi = -1e9, cnt = 0, lazy = 0;
    bool has=0;
    ll sum = 0;
};
struct segtree
{
    int n;
    vector<info>t;
    segtree(int n,vector<int>&a)
    {
        this->n = n;
        t.resize(n*4);
        build(1,0,n-1,a);
    }
    void Merge(info &node, info &l, info &r)
    {
        node.maxi = max(l.maxi, r.maxi) ;
        node.cnt = (node.maxi==l.maxi ? l.cnt : 0) + (node.maxi==r.maxi ? r.cnt : 0);
        node.sum = l.sum + r.sum;
        if(l.maxi != r.maxi)
            node.smaxi =max({ min(l.maxi, r.maxi) ,l.smaxi, r.smaxi});
        else
            node.smaxi = max(l.smaxi, r.smaxi);
    }
    void build(int node, int l,int r, vector<int>&a)
    {
        if(l==r)
        {
            t[node].maxi = a[l];
            t[node].cnt = 1;
            t[node].sum = a[l];
            return;
        }
        int mid= (l+r)/2;
        build(node*2, l, mid,a);
        build(node *2 +1, mid+1, r,a);
        Merge(t[node], t[node*2], t[node *2+1]);
    }
    void dop(int node, int add)
    {
        if(t[node].maxi <= add)
            return;
        t[node].sum -= t[node].maxi *1ll* t[node].cnt;
        t[node].maxi = add;
        t[node].sum += t[node].maxi *1ll* t[node].cnt;
        t[node].lazy= add;
        t[node].has = 1;
    }
    void push_down(int node)
    {
        if(t[node].has)
        {
            dop(node*2, t[node].lazy);
            dop(node*2+1, t[node].lazy);
            t[node].lazy =0;
            t[node].has = 0;
        }
    }
    void update(int node, int l,int r, int i, int j, int add)
    {
        if(l>j || r<i || t[node].maxi <= add)
        {
            return;
        }
        if(l>=i && r<=j && t[node].smaxi < add)
        {
            int x = t[node].maxi - add;
            t[node].sum -= t[node].maxi *1ll* t[node].cnt;
            t[node].maxi = add;
            t[node].sum += t[node].maxi *1ll* t[node].cnt;
            t[node].lazy= add;
            t[node].has = 1;
            return;
        }
        int mid = (l+r)/2;
        push_down(node);
        update(node *2, l,mid, i, j, add);
        update(node *2 +1, mid+1, r, i, j, add);
        Merge(t[node], t[node *2], t[node*2+1]);
    }
    void update(int l,int r, int add)
    {
        update(1,0,n-1,l,r,add);
    }
    pair<ll,int> query(int node, int l, int r, int i, int j)
    {
        if(l>j || r<i)
        {
            return make_pair(0,-1e9);
        }
        if(l>=i && r<=j)
        {
            return make_pair(t[node].sum,t[node].maxi);
        }
        int mid = (l+r)/2;
        push_down(node);
        pair<ll,int> x = query(node *2, l,mid, i, j);
        pair<ll,int> y = query(node *2 +1, mid+1, r, i, j);
        return make_pair(x.first+y.first , max(x.second,y.second));
    }
    pair<ll,int> query(int l, int r)
    {
        return query(1,0,n-1,l,r ) ;
    }
};
