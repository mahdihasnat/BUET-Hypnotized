for(int i=a._Find_first(); i< a.size(); i = a._Find_next(i))
mt19937 rng(chrono::steady_clock::now().
			time_since_epoch().count());
int getrand(int a, int b){
 int x = uniform_int_distribution<int>(a, b)(rng);
 return x;
}

l1.splice(l1.end(), l2);

merge(a.begin(), a.end(),
    b.begin(), b.end(),
    back_inserter(c));
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

struct custom_hash {
 static uint64_t splitmix64(uint64_t x) {
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
 }

 size_t operator()(uint64_t x) const {
  static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().
  time_since_epoch().count();
  return splitmix64(x + FIXED_RANDOM);
 }
};
unordered_map<long long, int, custom_hash> safe_map;

struct hash_pair {
 template <class T1, class T2>
 size_t operator()(const pair<T1, T2>& p) const {
  auto hash1 = hash<T1>{}(p.first);
  auto hash2 = hash<T2>{}(p.second);
  return hash1 ^ hash2;
 }
};
unordered_map<pair<int, int>, int, hash_pair> mp;
//mod inverse for all m
inv[1] = 1;
for(int i = 2; i < m; ++i)
 inv[i] = m - (m/i) * inv[m%i] % m;
//ordered set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int >,rb_tree_tag,
	tree_order_statistics_node_update>indexed_set;
//submask supermask
for (int s=m; s; s=(s-1)&m)
for (int mask=need; mask < (1<<n) ; mask = (mask+1)|need)
string str="abc def gh",buf;stringstream ss(str);
while(ss >> buf) cout << buf << endl;
