vector<int> SOS(vector<int> p, bool inverse, bool subset) {
int k = __builtin_ctz(p.size());
assert(p.size() == (1<<k));
for (int i=0; i<k; i++)
for (int mask=0; mask<(1<<k); mask++)
    if (bool(mask & (1<<i)) == subset) {
        if (!inverse) p[mask] =add(p[mask], p[mask^(1<<i)]);
        else          p[mask] =sub(p[mask], p[mask^(1<<i)]);
    }
return p;
}
vector<int> SubsetConvolution( vector<int> &a, vector<int> &b) {
int k = __builtin_ctz(a.size());
assert(a.size() == (1<<k) && b.size() == (1<<k));
vector<int> Z(1<<k);
vector<vector<int>> A(k+1, Z), B(k+1, Z), C(k+1, Z);
for (int mask=0; mask<(1<<k); mask++) {
A[__builtin_popcount(mask)][mask] = a[mask];
B[__builtin_popcount(mask)][mask] = b[mask];
}
for (int i=0; i<=k; i++) {
A[i] = SOS(A[i], 0, 1); B[i] = SOS(B[i], 0, 1);
for (int j=0; j<=i; j++)
    for (int mask = 0; mask < (1<<k); mask++)
        C[i][mask] =add(C[i][mask], gun(A[j][mask],B[i-j][mask]));
C[i] = SOS(C[i], 1, 1);
} vector<int> ans(1<<k);
for (int mask=0; mask<(1<<k); mask++) {
ans[mask] = C[__builtin_popcount(mask)][mask];
} return ans;
}