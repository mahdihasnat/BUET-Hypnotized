vector<int> basis[N];
int sz[N],a[N],LOGK = 21;
void insert_vector(vector<int>&basis ,int &sz, int mask){
 for(int i=0;i<LOGK;i++) {
  if(!(mask&(1<<i))) continue;
  if(!basis[i]) {
   basis[i] = mask; sz++; return;
  }
  mask^=basis[i];
 }
}
bool check(vector<int>&basis , int mask){
 for(int i=0;i<LOGK;i++) {
  if(!(mask&(1<<i))) continue;
  if(!basis[i]) { return 0; }
  mask ^= basis[i];
 }
 return 1;
}
