
ll extended_euclidean(ll a, ll b, ll & x, ll & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = extended_euclidean(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
ll mod_inverse(ll a,ll m)
{
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1)
    {
        cout << "No solution!";
        return -1;
    }
    else
    {
        x = (x % m + m) % m;
        return x;
    }
}

ll fact[N];
ll fact_inv[N];

ll ncr(ll n,ll r)
{
    if(r<0 or r>n) return 0;
	return fact[n]*fact_inv[r]%oo * fact_inv[n-r] % oo;
}
void init()
{
	fact[0]=1;
	for(ll i=1;i<N;i++) fact[i]=fact[i-1]*i % oo;
	fact_inv[N-1]=mod_inverse(fact[N-1],oo);
	for(ll i=N-2;i>=0;i--) fact_inv[i]=fact_inv[i+1]*(i+1) % oo;
}