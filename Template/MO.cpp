struct query{int l,r,idx;};
int block;
bool comp1(query p,query q){
 if (p.l / block != q.l / block) {
  if(p.l==q.l) return p.r<q.r;
  return p.l < q.l;
 }
 return (p.l / block & 1) ? (p.r < q.r) : (p.r > q.r);
}
void mos_algorithm(int n, vector<query>&queries){
 vector<int> answers(queries.size());
 block = (int)sqrt(n);
 sort(queries.begin(), queries.end(),comp1);
 int cur_l = 0;
 int cur_r = -1;
 for (query q : queries) {
  while (cur_l > q.l) {cur_l--; add(cur_l);}
  while (cur_r < q.r) {cur_r++;add(cur_r);}
  while (cur_l < q.l) {Remove(cur_l);cur_l++;}
  while (cur_r > q.r) {Remove(cur_r);cur_r--;}
  answers[q.idx] = get_answer();
 }
 for(int i:answers) {cout<<i<<"\n";}
}
