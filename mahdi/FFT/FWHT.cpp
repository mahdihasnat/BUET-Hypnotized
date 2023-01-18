/****************************
Hadamard Matrix -
1. For XOR-Convolution -
H = H_inverse = {{1, 1}, {1, -1}}
2.For AND-Convolution -
H         = {{0, 1}, {1, 1}}
H_inverse = {{-1, 1}, {1, 0}}
3. For OR-Convolution -
H         = {{1, 1}, {1, 0}}
H_inverse = {{0, 1}, {1, -1}}
***************************/
#define bitwiseXOR 1
//#define bitwiseAND 2
//#define bitwiseOR 3
const ll MOD = 1e9+7;

void FWHT(vector< ll >&p, bool inverse = false)
{
    ll n = p.size();
    assert((n&(n-1))==0);

    for (ll len = 1; 2*len <= n; len <<= 1) {
        for (ll i = 0; i < n; i += len+len) {
            for (ll j = 0; j < len; j++) {
                ll u = p[i+j];
                ll v = p[i+len+j];

                #ifdef bitwiseXOR
                p[i+j] =( u+v)%MOD;
                p[i+len+j] = (u-v)%MOD;
                #endif // bitwiseXOR

                #ifdef bitwiseAND
                if (!inverse) {
                    p[i+j] = v % MOD;
                    p[i+len+j] = (u+v) % MOD;
                } else {
                    p[i+j] = (-u+v+MOD) % MOD;
                    p[i+len+j] = u % MOD;
                }
                #endif // bitwiseAND

                #ifdef bitwiseOR
                if (!inverse) {
                    p[i+j] = u+v;
                    p[i+len+j] = u;
                } else {
                    p[i+j] = v;
                    p[i+len+j] = u-v;
                }
                #endif // bitwiseOR
            }
        }
    }

    #ifdef bitwiseXOR
    if (inverse) {
        for (ll i = 0; i < n; i++) {
//            assert(p[i]%n==0);
//            p[i]/=n;
            p[i]  = p[i] * mod_inverse(n,MOD) % MOD;
        }
    }
    #endif // bitwiseXOR
}
