const int N= 1e5+5;
int value[4*N];
int lazy[4*N];

void propagate(int u,int ss,int se)
{
    value[u]+= (se-ss+1) * lazy[u];
    if(ss!=se)
        lazy[u<<1] += lazy[u] , lazy[u<<1|1]+= lazy[u];
    lazy[u] = 0;
}
int func(int x,int y)
{
    return x+y;
}

void UpdateRange(int u , int ss, int se, int us,int ue, int diff)
{
    int mid = ss+(se-ss)/2;

    propagate(u,ss,se);

    if (ss>se || ss>ue || se<us)
        return ;

    if (ss>=us && se<=ue)
    {
        lazy[u] += diff;
        return propagate(u,ss,se);
    }


    UpdateRange(u<<1, ss, mid, us, ue, diff);
    UpdateRange(u<<1|1, mid+1, se, us, ue, diff);

    value[u]=func(value[u<<1],value[u<<1|1]);

}
int GetFunc(int u,int ss, int se, int qs, int qe)
{
    propagate(u,ss,se);
    
    int mid = ss+(se-ss)/2;

    if (ss>se || ss>qe || se<qs)
        return 0;

    if (ss>=qs && se<=qe)
        return value[u];

    return func(GetFunc(u<<1,ss,mid,qs,qe),GetFunc(u<<1|1,mid+1,se,qs,qe));
}

void Build(int u,int *a,int ss,int se)
{
    lazy[u]=0;
    if(ss==se)
    {
        value[u]=a[ss];
        return ;
    }
    int mid = ss+(se-ss)/2;
    Build(u<<1,a,ss,mid);
    Build(u<<1|1,a,mid+1,se);
    value[u]=func(value[u<<1],value[u<<1|1]);
}
