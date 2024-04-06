//  Minimum: M increasing, x dec, useless(s-1, s-2, s-3)
//           M decreasing, x inc, useless(s-3, s-2, s-1)
// Maximum: M increasing, x inc, useless(s-3, s-2, s-1)
//          M decreasing, x dec, useless(s-1, s-2, s-3)
vector<LL> M, C; int ptr = 0;
bool useless(int l1, int l2, int l3) { 
  return (C[l3]-C[l1])*(M[l1]-M[l2]) <= (C[l2]-C[l1])*(M[l1]-M[l3]); }
LL f(int id, LL x) { return M[id]*x+C[id]; }
void add(LL m, LL c) {
  M.push_back(m); C.push_back(c); int s = M.size();
  while (s >= 3 && useless(s-3, s-2, s-1)) {
    M.erase(M.end()-2); C.erase(C.end()-2); s--; } }
LL query2(LL x) { int lo=0, hi=M.size()-1;
  while(lo<hi) { int mid = (lo+hi)/2;
    if (f(mid, x) > f(mid+1, x)) lo = mid+1; /// change > to < for maximum
    else hi = mid;
  } return f(lo, x);
}