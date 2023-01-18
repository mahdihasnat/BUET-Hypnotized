//order[i][j]=indexOfMan i in j-th women'sListOfPreference
//prefer[i]=listOfWomen inOrderOf decreasingPreference
int n;
int pre[N][N],order[N][N],nxt[N];
queue<int>q;
int future_wife[N],future_husband[N];
void engage(int man , int woman){
 int m1 = future_husband[woman];
 if(m1==0) {
  future_wife[man] = woman;future_husband[woman] = man;
 }
 else{
  future_wife[man] = woman;future_husband[woman] = man;
  future_wife[m1] =0;q.push(m1);
 }
}

void TEST_CASES(int cas){
 while(!q.empty())q.pop();
 cin>>n;
 for(int i=1;i<=n;i++) {
  for(int j=1;j<=n;j++) {
   cin>>pre[i][j]; pre[i][j]-= n;
  }
  nxt[i] = 1;future_wife[i] = 0;q.push(i);
 }
 for(int i=1;i<=n;i++) {
  for(int j=1;j<=n;j++) {
   int x; cin>>x;
   order[i][x] = j;
  }
  future_husband[i] = 0;
 }
 while(!q.empty()) {
  int man = q.front(); q.pop();
  int woman = pre[man][nxt[man]++];
  if(future_husband[woman]==0) {
   engage(man , woman);
  }
  else if(order[woman][man] <  order[woman][future_husband[woman]]) {
   engage(man , woman);
  }
  else{ q.push(man); }
 }
 for(int i=1;i<=n;i++) {
  cout<<" ("<<i<<" "<<future_wife[i]+n<<")";
 }
}
