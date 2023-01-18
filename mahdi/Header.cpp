///****In the name of ALLAH, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cerr<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}
template <class T , size_t N>
ostream &operator <<(ostream &os,const array <T,N> &a)
{
	os<<"{";
	for(auto x: a)
		os<<x<<" ";
	os<<"}";
	return os;
}

template <class T>
ostream &operator <<(ostream &os,const vector<T> &a)
{
	os<<"{ ";
	for(auto x: a)
		os<<x<<" ";
	os<<"}";
	return os;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=3e5+5;
const int oo=1e9+7;

int32_t main()
{
    FastIO;
    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
    }
}
