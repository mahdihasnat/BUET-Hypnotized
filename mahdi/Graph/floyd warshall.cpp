const int N= 101;
int w[N][N];
void pre()
{
    memset(w,0x3f3f3f3f,sizeof w);
}
void floyd_warshall(int n)
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(w[i][j]>w[i][k]+w[k][j])
                    w[i][j]= w[i][k]+w[k][j];
}

