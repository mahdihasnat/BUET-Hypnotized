namespace my_gcc_ints {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    using int128 = __int128;
#pragma GCC diagnostic pop
}


std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
istream & operator>>(istream &in,__int128_t & val)
{
    int sign=1,i=0;
    val=0;
    string s;
    in>>s;
    if(s[i]=='-')
        sign=-1,i=1;
    for(;i<s.size();i++)
    {
        val*=10;
        val+=s[i]-'0';
    }
    val*=sign;

    return in;
}
ll addmod( ll x, ll y, ll m )
{
  x %= m;
  y %= m;
  ll sum = x-m+y; // -m <= sum < m-1
  return sum < 0 ? sum + m : sum;
}

ll timesmod( ll x, ll y, ll m )
{
  x %= m;
  y %= m;
  ll a = x < y ? x : y; // min
  ll b = x < y ? y : x; // max
  ll product = 0;
  for (; a != 0; a >>= 1, b = addmod(b,b,m) )
    if (a&1) product = addmod(product,b,m);
  return product;
}
