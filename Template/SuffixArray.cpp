const int LOG = 20;
int sa[N],Data[N],rnk[N],height[N];
int wa[N],wb[N],wws[N],wv[N];
int lg[N], rmq[N][LOG];
void prelg() {
 lg[0] = lg[1] = 0;
 for(int i = 2; i < N; i++) {
  lg[i] = lg[i/2] + 1;
 }
}
struct SuffixArray {
 int n;
 int cmp(int *r,int a,int b,int l) {
  return (r[a]==r[b]) && (r[a+l]==r[b+l]);
 }
 void DA(int *r,int *sa,int n,int m) {
  int i,j,p,*x=wa,*y=wb,*t;
  for(i=0; i<m; i++) wws[i]=0;
  for(i=0; i<n; i++) wws[x[i]=r[i]]++;
  for(i=1; i<m; i++) wws[i]+=wws[i-1];
  for(i=n-1; i>=0; i--) sa[--wws[x[i]]]=i;
  for(j=1,p=1; p<n; j*=2,m=p)
  {
   for(p=0,i=n-j; i<n; i++) y[p++]=i;
   for(i=0; i<n; i++)
    if(sa[i]>=j) y[p++]=sa[i]-j;
   for(i=0; i<n; i++) wv[i]=x[y[i]];
   for(i=0; i<m; i++) wws[i]=0;
   for(i=0; i<n; i++) wws[wv[i]]++;
   for(i=1; i<m; i++) wws[i]+=wws[i-1];
   for(i=n-1; i>=0; i--) sa[--wws[wv[i]]]=y[i];
   for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
    x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
  }
 }
 void calheight(int *r,int *sa,int n) {
  int i,j,k=0;
  for(i=1; i<=n; i++) rnk[sa[i]]=i;
  for(i=0; i<n; height[rnk[i++]]=k)
   for(k?k--:0,j=sa[rnk[i]-1]; r[i+k]==r[j+k]; k++);
 }
 void suffix_array (string  &A) {
  n = A.size();
  Data[n]=0;
  int cnt =0;
  for (int i = 0; i < n; i++){
   Data[i] = A[i]-'a'+1; //careful
   cnt = max(cnt,  Data[i]);
  }
  DA(Data,sa,n+1,cnt+1);
  calheight(Data,sa,n);
  for(int i = 0; i < n; i++)
   sa[i] = sa[i+1], height[i] = height[i+1], rnk[sa[i]] = i;
  range_lcp_init();
 }
 /** LCP for range : build of rmq table **/
 void range_lcp_init() {
  for(int i = 0; i < n; i++)
   rmq[i][0] = height[i];
  for(int j = 1; j < LOG; j++) {
   for(int i = 0; i < n; i++) {
    if (i+(1<<j)-1 < n)
     rmq[i][j] = min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
    else break;
   }
  }
 }
 /** lcp between l'th to r'th suffix in suffix array **/
 int query_lcp(int l, int r) {
  assert(l <= r); assert(l>=0 && l<n && r>=0 && r<n);
  if(l == r) return n-sa[l];
  l++;
  int k = lg[r-l+1];
  return min(rmq[l][k],rmq[r-(1<<k)+1][k]);
 }
 //i and j position in original string
 int getsuff(int i, int j) {
  i= rnk[i];j = rnk[j];
  return query_lcp(min(i,j),max(i,j));
 }
} SA;
