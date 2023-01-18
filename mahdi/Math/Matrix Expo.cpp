
const int DIMENSION = 4;
const int mod = 10007;


int sub(int x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
    return x;
}

int add(int x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int mul(int x, int y)
{
    return (1ll * x * y) % mod;
}

struct Matrix
{
    int a[DIMENSION][DIMENSION];

    Matrix()
    {
        for (int i = 0; i < DIMENSION; ++i)
            fill(a[i], a[i] + DIMENSION, 0);
    }

    int* operator[](int x)
    {
        return a[x];
    }

    Matrix operator * (Matrix &to)
    {
        Matrix ans;
        for (int i = 0; i < DIMENSION; ++i)
            for (int j = 0; j < DIMENSION; ++j)
                for (int k = 0; k < DIMENSION; ++k)
                    ans[i][j] = add(ans[i][j], mul(a[i][k], to[k][j]));
        return ans;
    }
    Matrix operator + ( const Matrix &to)
    {
        Matrix ans;
        for(int i=0; i<DIMENSION; i++)
        {
            for(int j=0; j<DIMENSION; j++)
                ans.a[i][j]= a[i][j]+to.a[i][j];
        }
        return ans;
    }

    vector<int> operator * (vector<int> to)
    {
        vector<int> ans(DIMENSION);
        for (int i = 0; i < DIMENSION; ++i)
        {
            ans[i]=0;
            for (int j = 0; j < DIMENSION; ++j)
                ans[i] = add(ans[i], mul(a[i][j], to[j]));
        }
        return ans;
    }
    friend ostream &operator<<(ostream &os,const Matrix &m)
    {
        os<<"{ ";
        for(int i=0;i<DIMENSION;i++)
        {
            os<<"[";
            for(int j=0;j<DIMENSION;j++) os<<" "<<m.a[i][j];
            os<<"]";
            os<<",";
        }
        os<<" }";
        return os;
    }

} ONE;

void init()
{
    for(int i=0;i<DIMENSION;i++)
        ONE[i][i]=1;
}

Matrix bin(Matrix A, long long n)
{
    Matrix B = ONE;
    while (n)
    {
        if (n & 1)
            B = B * A;
        A = A * A;
        n >>= 1;
    }
    return B;
}
