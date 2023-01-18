const int N= 1e5+5;
int value[4*N];
int func(int i,int j)
{
    return i+j;
}
void UpdatePoint(int node , int ss, int se, int u, int diff)
{
    int mid = ss+(se-ss)/2;

    if (ss>se || ss>u || se<u)
        return ;

    if (ss==se&& ss==u)
    {
        value[node] += diff;
        return;
    }

    UpdatePoint(node<<1, ss, mid, u, diff);
    UpdatePoint((node<<1)+1, mid+1, se, u, diff);

    value[node]=func(value[node<<1],value[(node<<1)+1]);

}
int Getfunc(int node,int ss, int se, int qs, int qe)
{
    propagate(u,ss,se);

    int mid = ss+(se-ss)/2;

     if (ss>se || ss>qe || se<qs || qs>qe)
        return 0;

    if (ss>=qs && se<=qe)
        return value[node];

    return func(Getfunc(node<<1,ss,mid,qs,qe),Getfunc((node<<1)+1,mid+1,se,qs,qe));
}

void Build(int node,int *a,int ss,int se)
{
    if(ss==se)
    {
        value[node]=a[ss];
        return ;
    }
    int mid = ss+(se-ss)/2;
    Build(node<<1,a,ss,mid);
    Build((node<<1)+1,a,mid+1,se);
    value[node]=func(value[node<<1],value[(node<<1)+1]);
}
