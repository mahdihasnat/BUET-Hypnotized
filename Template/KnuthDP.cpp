int n,k;int a[N];ll dp[N][N];int opt[N][N];int cost[N][N];
void TEST_CASES(){
 memset(dp,0,sizeof dp);
 for(int i=1;i<=n;i++){opt[0][i] = 0;}
 for(int i=1;i<=k;i++){opt[i][n+1] = n;}
 for(int group = 1;group<=k;group++){
  for(int i=n;i>=1;i--){
   for(int last = opt[group-1][i];last<= opt[group][i+1];last++){
    ll val = dp[group-1][last] + cost[last+1][i];
    if(val>dp[group][i]){
     dp[group][i] = val;
	 opt[group][i] = last;
    }
   }
  }
 }
 cout<<dp[k][n]<<"\n";
}
