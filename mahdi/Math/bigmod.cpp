int bigmod ( int a, ll p, int m )
{
    int res = 1;
    int x = a;

    while ( p )
    {
        if ( p & 1 ) //p is odd
        {
            res = ( res *1LL* x ) % m;
        }
        x = ( x *1LL* x ) % m;
        p = p >> 1;
    }

    return res;
}