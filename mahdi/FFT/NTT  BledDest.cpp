const int LOGN = 20;
const int N = (1 << LOGN);
const int MOD = 998244353;
const int g = 3;

vector<int> w[LOGN];
vector<int> iw[LOGN];
vector<int> rv[LOGN];


inline int mul(int a, int b)
{
	return (a * 1ll * b) % MOD;
}

inline int norm(int a)
{
	while(a >= MOD)
		a -= MOD;
	while(a < 0)
		a += MOD;
	return a;
}

inline int binPow(int a, int k)
{
	int ans = 1;
	while(k > 0)
	{
		if(k & 1)
			ans = mul(ans, a);
		a = mul(a, a);
		k >>= 1;
	}
	return ans;
}

inline int inv(int a)
{
	return binPow(a, MOD - 2);
}



void precalc_fft()
{
	int wb = binPow(g, (MOD - 1) / (1 << LOGN));

	for(int st = 0; st < LOGN; st++)
	{
		w[st].assign(1 << st, 1);
		iw[st].assign(1 << st, 1);

		int bw = binPow(wb, 1 << (LOGN - st - 1));
		int ibw = inv(bw);

		int cw = 1;
		int icw = 1;

		for(int k = 0; k < (1 << st); k++)
		{
			w[st][k] = cw;
			iw[st][k] = icw;

			cw = mul(cw, bw);
			icw = mul(icw, ibw);
		}

		rv[st].assign(1 << st, 0);

		if(st == 0)
		{
			rv[st][0] = 0;
			continue;
		}
		int h = (1 << (st - 1));
		for(int k = 0; k < (1 << st); k++)
			rv[st][k] = (rv[st - 1][k & (h - 1)] << 1) | (k >= h);
	}
}


inline void fft(int a[N], int n, int ln, bool inverse)
{
	for(int i = 0; i < n; i++)
	{
		int ni = rv[ln][i];
		if(i < ni)
			swap(a[i], a[ni]);
	}

	for(int st = 0; (1 << st) < n; st++)
	{
		int len = (1 << st);
		for(int k = 0; k < n; k += (len << 1))
		{
			for(int pos = k; pos < k + len; pos++)
			{
				int l = a[pos];
				int r = mul(a[pos + len], (inverse ? iw[st][pos - k] : w[st][pos - k]));

				a[pos] = norm(l + r);
				a[pos + len] = norm(l - r);
			}
		}
	}

	if(inverse)
	{
		int in = inv(n);
		for(int i = 0; i < n; i++)
			a[i] = mul(a[i], in);
	}
}

int aa[N], bb[N], cc[N];

inline void multiply(int a[N], int sza, int b[N], int szb, int c[N], int &szc)
{
	int n = 1, ln = 0;
	while(n < (sza + szb))
		n <<= 1, ln++;
	for(int i = 0; i < n; i++)
		aa[i] = (i < sza ? a[i] : 0);
	for(int i = 0; i < n; i++)
		bb[i] = (i < szb ? b[i] : 0);

	fft(aa, n, ln, false);
	fft(bb, n, ln, false);

	for(int i = 0; i < n; i++)
		cc[i] = mul(aa[i], bb[i]);

	fft(cc, n, ln, true);

	szc = n;
	for(int i = 0; i < n; i++)
		c[i] = cc[i];
}
