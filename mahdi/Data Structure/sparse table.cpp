const int N=3e5+5;
const int K = 23 ; /// k >= ceil(lg22(n)) +1
int arr[N];
int st[N][K + 1];
int lg2[N+1];
void ini()
{
    lg2[1] = 0;
    for (int i = 2; i <= N; i++)
        lg2[i] = lg2[i/2] + 1;
}
int f(int i,int j)
{
    if(arr[i]==arr[j]) return i<j ? j: i;
    return arr[i]<arr[j] ? i: j;
}

void pre( int n)
{

    for (int i = 0; i < n; i++)
        st[i][0] = f( i,i);

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = f( st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}
int getf( int L,int R)
{
    if(L>R) swap(L,R);
    int j = lg2[R - L + 1];
    return  f(st[L][j], st[R - (1 << j) + 1][j]);
}
