int nod(int n)
{
    int ret=1;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            int p=0;
            while(n%i==0)
            {
                p++;
                n/=i;
            }
            ret*=p+1;
        }
    }
    if(n>1) ret*=2;
    return ret;
}
