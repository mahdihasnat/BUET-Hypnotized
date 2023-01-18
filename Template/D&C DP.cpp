int dp_before[N],dp_cur[N],cnt[N],l=0,r=-1,cur;
void add(int idx){
 cnt[a[idx]]++; if(cnt[a[idx]]==1)cur++;
}
void remove(int idx){
 cnt[a[idx]]--; if(cnt[a[idx]]==0) cur--;
}
int cost(int L,int R){
 while (l > L) { l--; add(l); }
 while (r < R) { r++; add(r); }
 while (l < L) { remove(l); l++; }
 while (r > R) { remove(r);r--;}
 return cur;
}
void compute(int l, int r, int optl, int optr){
 if (l > r) return;
 int mid = (l + r) >> 1;
 pair<int, int> best = {-1e9, -1};
 for (int k = optl; k <= min(mid, optr); k++) {
  if(best.second==-1) { best = {dp_before[k] +cost(k+1, mid), k};}
  else { best = max(best, {dp_before[k] +cost(k+1, mid), k}); }
 }
 dp_cur[mid] = best.first; int opt = best.second;
 compute(l, mid - 1, optl, opt);compute(mid + 1, r, opt, optr);
}
