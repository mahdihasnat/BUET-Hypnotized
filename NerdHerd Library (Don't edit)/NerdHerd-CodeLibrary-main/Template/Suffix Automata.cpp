struct state{
 int len, link;
 map<char, int> next;
 ll dp=-1; //number of paths
 ll cnt=0; //endpos size
 bool is_cloned=false;
 vector<int>inv_link;
};
struct SA {
 vector<state> st;
 int sz, last;
 void sa_init() {
  st[0].len = 0;
  st[0].link = -1;
  sz=0;
  sz++;
  last = 0;
 }
 void sa_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
   st[p].next[c] = cur;
   p = st[p].link;
  }
  if (p == -1) {
   st[cur].link = 0;
  }
  else {
   int q = st[p].next[c];
   if (st[p].len + 1 == st[q].len){
    st[cur].link = q;
   }
   else {
    int clone = sz++;
    st[clone].len = st[p].len + 1;
    st[clone].next = st[q].next;
    st[clone].link = st[q].link;
    while (p != -1 && st[p].next[c] == q) {
     st[p].next[c] = clone;
     p = st[p].link;
    }
    st[q].link = st[cur].link = clone;
    st[clone].is_cloned=true;
   }
  }
  last = cur;
 }
 ll run(int idx) {
  if(st[idx].dp!=-1)
   return st[idx].dp;
  if(idx!=0)
   st[idx].dp=st[idx].cnt;
  else st[idx].dp=0;
  for(char c='a';c<='z';c++) {
   if(!st[idx].next.count(c))
    continue;
   int u=st[idx].next[c];
   st[idx].dp+=run(u);
  }
  return st[idx].dp;
 }
 void dfs_in_tree(int idx) {
  if(st[idx].is_cloned==false) {
   st[idx].cnt=1;
  }
  for(int u:st[idx].inv_link) {
   dfs_in_tree(u);
   st[idx].cnt+=st[u].cnt;
  }
 }
 void build(string &s) {
  st.resize(2*(int)s.size());
  sa_init();
  for(char c:s) {
   sa_extend(c);
  }
  for(int i=1;i<sz;i++) {
   st[st[i].link].inv_link.push_back(i);
  }
  dfs_in_tree(0);
 }
};

