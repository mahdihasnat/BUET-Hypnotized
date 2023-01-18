const ll INF = 4e18;
//Point update and range min
struct Node {
 int l=-1,r=-1; pii val;
 Node(pii v, int l=-1, int r=-1) {
  this->l = l;
  this->r = r;
  val = v;
 }
};
vector<Node>nodes;
inline void Merge(Node &a, Node &b, Node &c) {
 a.val = min(b.val,c.val);
}
int build(int tl, int tr) {
 if (tl == tr) {
  nodes.emplace_back(make_pair(INF, -1));
  return (int)nodes.size()-1;
 }
 int tm = (tl + tr) / 2;
 int Left = build(tl, tm);
 int Right = build(tm+1, tr);
 nodes.emplace_back(make_pair(INF, -1),Left,Right);
 Merge(nodes.back(), nodes[Left], nodes[Right]);
 return (int)nodes.size()-1;
}

int update(int v, int tl, int tr, int pos, pii val) {
 if (tl == tr) {
  nodes.emplace_back(val);
  return (int)nodes.size()-1;
 }
 int tm = (tl + tr) / 2; int Left,Right;
 if (pos <= tm) {
  Left = update(nodes[v].l, tl, tm, pos,val);
  Right = nodes[v].r;
 }
 else {
  Left = nodes[v].l;
  Right = update(nodes[v].r, tm+1, tr, pos,val);
 }
 nodes.emplace_back(make_pair(INF, -1),Left,Right);
 Merge(nodes.back(), nodes[Left], nodes[Right]);
 return (int)nodes.size()-1;
}

pii query(int v, int tl, int tr, int a, int b) {
 if (a>tr|| tl>b || tl > tr) return {INF, -1};
 if(tl >=a && tr <=b) return nodes[v].val;
 int mid= (tl+tr)/2;
 return min(query(nodes[v].l,tl, mid, a,b), query(nodes[v].r, mid+1, tr, a, b));
}
