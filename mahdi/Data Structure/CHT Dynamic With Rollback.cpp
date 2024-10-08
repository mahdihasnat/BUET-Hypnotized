
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

///convex hull for maximizing
///in case of minimization, just insert(-m,-c) and negate the result for query
///Source: KATCL, Anachor

 
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
	friend ostream& operator<<(ostream& os, const Line& l) {
		return os << "{" << l.k << "," << l.m << "," << l.p << "}";
	}
};
 
struct CHT: multiset<Line, less<>> {
 
	stack< vector< pair<bool, Line> > > st;
	vector< pair<bool, Line> > cur;
 
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
 
 
	void add(ll k, ll m) {
		
		cur.clear();
 
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
		
		st.push(cur);
 
	}
	iterator insert(Line const & l)
	{
		cur.push_back({1, l});
		return multiset::insert(l);
	}
 
	iterator erase(iterator x) {
		cur.push_back({0, *x});
		return multiset::erase(x);
	}
 
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
 
	void rollback()
	{
		assert(!st.empty());
		auto &v = st.top();
		// DBG(v);
		for(auto [t, l]: v)
		{
			if(!t) insert(l);
			else erase(find(l));
		}
		st.pop();
	}
 
	friend ostream& operator<<(ostream& os, const CHT& cht) {
		os << "{";
		for (auto& l : cht) os << l << ", ";
		return os << "}";
	}
 
} ch;



/// Solves https://judge.yosupo.jp/problem/line_add_get_min
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    for (int i=0; i<n; i++) {
        long long x, y;
        cin>>x>>y;
        ch.add(-x, -y);
    }

    for (int i=0; i<q; i++) {
        long long t, x, y;
        cin>>t;

        if (!t) {
            cin>>x>>y;
            ch.add(-x, -y);
        }
        else {
            cin>>x;
            cout<<-ch.query(x)<<"\n";
        }
    }
}