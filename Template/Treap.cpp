mt19937 rng(chrono::steady_clock::now().
time_since_epoch().count());
int getrand(int a, int b){
 int x = uniform_int_distribution<int>(a, b)(rng);
 return x;
}
struct treap{
 int prior,val,subtreeSize ;
 treap *l;treap *r;treap *parent;
 int sum,lazy;
 treap(int data) {
  val= data;prior = getrand(-2e9, 2e9);
  subtreeSize = 1;
  l=NULL;r=NULL;parent = NULL;lazy = 0;sum = data;
 }
};
typedef treap* ptreap;
int Size(ptreap t){
 if(t)return t->subtreeSize;
 return 0;
}
void update_size(ptreap t){
 if(t) t->subtreeSize = 1+ Size(t->l) + Size(t->r);
}
void push(ptreap t){
 if(!t || !t->lazy) {return;}
 t->val += t->lazy;t->sum += t->lazy * Size(t);
 if(t->l) t->l->lazy += t->lazy;
 if(t->r) t->r->lazy += t->lazy;
 t->lazy = 0;
}
void reset(ptreap t){
 if(t) t->sum = t->val;
}
void combine(ptreap &t, ptreap l, ptreap r){
 if(!l || !r) {if(l) {t= l;}else {t = r;}return;
 }
 t->sum = l->sum + r->sum;
}
void operation(ptreap t){
 if(!t)return;
 reset(t);push(t->l);push(t->r);
 combine(t,t,t->l);combine(t,t,t->r);
}
void split(ptreap t, ptreap &l, ptreap &r, int pos, int add =0){
 if(!t) {l = NULL;r = NULL;return;}
 push(t);
 int curr = add + Size(t->l);
 if(curr<=pos) {
  split(t->r, t->r, r, pos, curr+1);
  if(t->r != NULL) t->r->parent = t;
  if(r!=NULL) r->parent = NULL;
  l = t;
 }
 else {
  split(t->l, l, t->l,pos, add);
  if(t->l != NULL) {t->l->parent = t;
  }
  if(l!=NULL) {l->parent = NULL;}
  r =t;
 }
 update_size(t);operation(t);
}
void Merge(ptreap &t, ptreap l, ptreap r){
 push(l);push(r);
 if(!l || !r) {if(l) t= l;else t = r;}
 else if(l->prior > r->prior) {
  Merge(l->r, l->r, r);
  if(l->r != NULL) {l->r ->parent = l;}
  t= l;
 }
 else {
  Merge(r->l, l, r->l);
  if(r->l != NULL) {r->l->parent = r;}
  t = r;
 }
 update_size(t);operation(t);
}
int range_query(ptreap t, int l, int r){
 ptreap t1, t2, t3;
 split(t,t1,t2,l-1);split(t2,t2,t3,r-l);
 int ans = t2->sum;
 Merge(t,t1,t2);Merge(t,t,t3);
 return ans;
}
void range_update(ptreap t, int l,int r, int val){
 ptreap t1, t2, t3;
 split(t,t1,t2,l-1);split(t2,t2,t3,r-l);
 t2->lazy += val;Merge(t,t1,t2);Merge(t,t,t3);
}
ptreap goup(ptreap t){
 if(t==NULL || t->parent==NULL) return t;
 return goup(t->parent);
}
void output2 (ptreap t){
 if (!t) return;
 push (t);output2 (t->l);
 cout<<t->val<<" ";output2 (t->r);
}
