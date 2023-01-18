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
void for_all_mod_inverse(ll m)
{
    inv[1] = 1;
    for(ll i = 2; i < m; ++i)
        inv[i] = (m - (m/i) * inv[m%i] % m) % m;
}
