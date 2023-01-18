vector<int>dp(n,0);
vector<int>newdp(n);
for(int i=1; i<=m; i++){
int koto = d*(a[i].t - a[i-1].t);
deque<pair<int,int> >dq;
int l = 0 , r= -1;
for(int j=0; j<n; j++){
 int eil = max(0ll, j-koto) , eir = min(n-1,j+koto);
 while(!dq.empty() && dq.front().first < eil) {
  dq.pop_front();
 }
 while(r!= eir) {
  r++;
  int val = dp[r];
  int idx = r;
  while(!dq.empty() && dq.back().second <= val) {
   dq.pop_back();
  }
  dq.push_back({idx,val});
 }
 newdp[j] = a[i].b - abs(a[i].a - j-1) + dq.front().second ;
}
swap(dp,newdp);
}
cout<<*max_element(dp.begin(), dp.end())<<"\n";
