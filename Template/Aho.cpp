const int K = 26;
struct Node{
public:
 vector<int>nxt; vector<int>go;
 int suf ; int ssuf;
 bool leaf; 
 int parent; int ch;
 Node(int p=-1,int ch = -1) {
  this->parent = p; this->ch = ch;
  nxt.resize(K,-1); go.resize(K,-1);
  leaf = false; suf = -1;
  ssuf = -1;
 }
};
struct AhoCorasick{
 vector<Node>nodes;
 AhoCorasick() {
  nodes.emplace_back(Node());
 }
 int get_num(char ch) {
  int ret = ch-'a'; return ret;
 }
 void add_string(string &s) {
  int v =0;
  for(int i=0; i<s.size(); i++) {
   int now = get_num(s[i]);
   if(nodes[v].nxt[now]==-1) {
    nodes[v].nxt[now] = nodes.size();
    nodes.emplace_back(v,now);
   }
   v = nodes[v].nxt[now];
  } nodes[v].leaf = true;
 }
 int go(int v, int ch) {
  int &ret = nodes[v].go[ch];
  if(ret!=-1) return ret;
  if(nodes[v].nxt[ch]!=-1) {
   return ret = nodes[v].nxt[ch];
  }
  if(v==0) { return ret = 0; }
  return ret = go(get_link(v), ch);
 }
 int get_link(int v) {
  int &ret = nodes[v].suf;
  if(ret!=-1) return ret;
  if(v==0 || nodes[v].parent==0) 
  { return ret =0; }
  return ret = go(get_link(nodes[v].parent) , nodes[v].ch);
 }
 int exit_link(int v) {
  int &ret = nodes[v].ssuf;
  if(ret!=-1) return ret;
  if(v==0 || nodes[v].parent==0) 
  { return ret = 0; }
  int s = get_link(v);
  if(nodes[s].leaf) 
  	{ return ret = s; }
  return ret = exit_link(s);
 }
 void feed(string &s) {
  int v =0;
  for(int i=0;i<s.size();i++) {
   int ch = get_num(s[i]);
   v = go(v,ch); int u  =v ;
   while(u!=0) 
   	{ u = exit_link(u); }
  }
 }
};


