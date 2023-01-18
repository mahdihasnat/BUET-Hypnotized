
const int NUMBER_OF_HASH = 2;
struct Hash
{
    ll a[NUMBER_OF_HASH];
    Hash operator + (const ll &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = a[i] + h;  return ret;}
    Hash operator + (const Hash &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = a[i] + h.a[i];  return ret;}
    Hash operator ^ (const Hash &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = a[i] ^ h.a[i];  return ret;}
    Hash operator - (const Hash &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = a[i] - h.a[i];  return ret;}
    Hash operator * (const Hash &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = a[i] * h.a[i];  return ret;}
    Hash operator % (const Hash &h ) { Hash ret ; for(int i=0;i<NUMBER_OF_HASH;i++) ret.a[i] = (a[i] % h.a[i]+h.a[i])%h.a[i];  return ret;}
    bool operator== (const Hash &h ) { bool ret=1;for(int i=0;i<NUMBER_OF_HASH;i++) ret = ret and a[i] == h.a[i] ; return ret;}
    friend ostream &operator <<(ostream &os , const Hash & h)
    {
        os<<"{";
        for(int i=0;i<NUMBER_OF_HASH;i++)
            os<<","<<h.a[i];
        os<<"}";
        return os;
    }

};

Hash bigmod ( Hash a, long long p, Hash m )
{
    Hash res = {1,1};
    Hash x = a;

    while ( p )
    {
        if ( p & 1 ) //p is odd
        {
            res = ( res * x ) % m;
        }
        x = ( x * x ) % m;
        p = p >> 1;
    }

    return res;
}



const Hash MOD = {(ll)1e9+7 ,(ll)1e9+9};
const Hash BASE = { (ll)(1e8 + 5e4 + 1) ,(ll) 1e9 + 87};

Hash paw[N];
Hash inv_paw[N];
Hash h[N];

void precal(int n)
{
    assert(n<=N);
    paw[0]= { 1, 1};
    for(int i=1;i<n;i++)
        paw[i] = paw[i-1] * BASE % MOD;
}
void init(const string &s)
{
    h[0] = {0,0};
    for(int i=0;i<s.size();i++)
        h[i+1]= (h[i]*BASE+s[i] ) %MOD;
}

inline Hash hashval(int l,int r) /// l,r 0 indexed
{
    return (h[r+1]-h[l]*paw[r-l+1])%MOD;
}
