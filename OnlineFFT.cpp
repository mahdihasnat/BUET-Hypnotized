//Computing F_i=sum(1<=j<i)F_j*G_n-j
void convolve(int l1,int r1,int l2,int r2) {
    A=F[l1..r1]; //0 indexed
    B=G[l2..r2];
    C=A*B;
    for(int i=0;i<C.size();++i)
        F[l1+l2+i]+=C[i];
}
F[1]=1;//Base
for(int i=1;i<=n-1;i++)
{
    F[i+1]+=F[i]*G[1]; F[i+2]+=F[i]*G[2];
    for(int pw=2;i%pw==0&&pw+1<=n;pw=pw*2) {
        convolve(i-pw,i-1,pw+1,min(2*pw,n));
    }
}
