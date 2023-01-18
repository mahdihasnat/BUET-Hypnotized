const int inv2 = (mod + 1) >> 1;
const int M = (1 << 20);
const int OR = 0;
const int AND = 1;
const int XOR = 2;
struct FWHT{
 int P1[M], P2[M];
 void wt(int *a, int n, int flag = XOR) {
  if (n == 0)
   return;
  int m = n / 2;
  wt(a, m, flag);
  wt(a + m, m, flag);
  for (int i = 0; i < m; i++) {
   int x = a[i], y = a[i + m];
   if (flag == OR)
    a[i] = x, a[i + m] = (x + y) % mod;
   if (flag == AND)
    a[i] = (x + y) % mod, a[i + m] = y;
   if (flag == XOR)
    a[i] = (x + y) % mod, a[i + m] = (x - y + mod) % mod;
  }
 }
 void iwt(int* a, int n, int flag = XOR) {
  if (n == 0)
   return;
  int m = n / 2;
  iwt(a, m, flag);
  iwt(a + m, m, flag);
  for (int i = 0; i < m; i++) {
   int x = a[i], y = a[i + m];
   if (flag == OR)
    a[i] = x, a[i + m] = (y - x + mod) % mod;
   if (flag == AND)
    a[i] = (x - y + mod) % mod, a[i + m] = y;
   if (flag == XOR)
    a[i] = 1LL * (x + y) * inv2 % mod, a[i + m] = 1LL * (x - y + mod) * inv2 % mod; // replace inv2 by >>1 if not required
  }
 }
 vector<int> multiply(int n, vector<int> A, vector<int> B, int flag = XOR) {
  assert(__builtin_popcount(n) == 1);
  A.resize(n);
  B.resize(n);
  for (int i = 0; i < n; i++)
   P1[i] = A[i];
  for (int i = 0; i < n; i++)
   P2[i] = B[i];
  wt(P1, n, flag);
  wt(P2, n, flag);
  for (int i = 0; i < n; i++)
   P1[i] = 1LL * P1[i] * P2[i] % mod;
  iwt(P1, n, flag);
  return vector<int> (P1, P1 + n);
 }
 vector<int> pow(int n, vector<int> A, long long k, int flag = XOR) {
  assert(__builtin_popcount(n) == 1);
  A.resize(n);
  for (int i = 0; i < n; i++)
   P1[i] = A[i];
  wt(P1, n, flag);
  for(int i = 0; i < n; i++)
   P1[i] = POW(P1[i], k);
  iwt(P1, n, flag);
  return vector<int> (P1, P1 + n);
 }
} t;
int32_t main(){
 int n;
 cin >> n;
 vector<int> a(M, 0);
 for(int i = 0; i < n; i++) {
  int k;
  cin >> k;
  a[k]++;
 }
 vector<int> v = t.pow(M, a, n+1, AND);
 int ans = 1;
 for(int i = 1; i < M; i++)
  ans += v[i] > 0;
 cout << ans << '\n';
 return 0;
}
