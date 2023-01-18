/* try to avoid vector. Possibly use STL array or pointers */
void multiply(vector<vector<int> >&a, vector<vector<int> >&b){
 int n = a.size(), m= a[0].size(), l = b[0].size();
 vector<vector<int> >ret(n,vector<int>(l));
 for(int i=0; i<n; i++) {
  for(int k=0; k<m; k++) {
   for(int j=0; j<l; j++) {
    ret[i][j] = add(ret[i][j], gun(a[i][k],b[k][j],mod),mod);
   }
  }
 }
 swap(ret,a);
}

void bigmod(vector<vector<int> >&a, int p){
 int n = a.size();
 assert(a.size()==a[0].size());
 vector<vector<int> >res(n,vector<int> (n));
 for(int i=0; i<n; i++) {
  for(int j=0; j<n; j++) {
   res[i][j] = 0;
   if(i==j)
    res[i][j]=1;
  }
 }
 while(p) {
  if(p&1) {
   multiply(res,a);
  }
  multiply(a,a);
  p>>=1;
 }
 swap(a, res);
}
