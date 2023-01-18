/**
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q less than N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: fuzz-tested for n <= 300
 */

typedef __int128_t lll;

struct Frac{
 lll p, q;
};

template<class F>
Frac fracBS(F f, lll N){
 bool dir = 1, A = 1, B = 1;
 Frac lo{0, 1}, hi{1, 0};
 if (f(lo))
  return lo;
 assert(f(hi));
 while (A || B) {
  lll adv = 0, step = 1;
  for (int si = 0; step; (step *= 2) >>= si) {
   adv += step;
   Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
   if ((mid.p < 0 ? -mid.p : mid.p) > N || mid.q > N || dir == !f(mid)) {
    adv -= step;
    si = 2;
   }
  }
  hi.p += lo.p * adv;
  hi.q += lo.q * adv;
  dir = !dir;
  swap(lo, hi);
  A = B;
  B = !!adv;
 }
 return dir ? hi : lo;
}

int main(){
 Frac target = fracBS([&](Frac fr) {
  if (fr.q == 0)
   return true;
  return minfr < fr;
 }, mid);
}
