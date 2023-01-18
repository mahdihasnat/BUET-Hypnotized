typedef pair<int,int> pii;
struct point{
 int x, y;
 bool operator <(point &p) const{
  if(x==p.x){
   return y > p.y;
  }
  return x<p.x;
 }
};
struct line{
 point p1, p2;
 line(){}
 line(point &p, point &q){
  p1 = p;
  p2 = q;
 }
 bool operator <(line &p){
  ll a = (p1.x- p2.x);
  ll b = (p1.y-p2.y);
  ll c = (p.p1.x- p.p2.x);
  ll d = (p.p1.y-p.p2.y);
  return a*d < b*c;
 }
};
void TEST_CASES(int cas){
 int n;
 scanf("%d",&n);
 map<pii, int>mp;
 vector<point>v(n);
 for(int i=0; i<n; i++){
  v[i].read();
 }
 sort(v.begin(),v.end());
 for(int i=0; i<n; i++){
  mp[ {v[i].x, v[i].y}] = i;
 }
 vector<line>lines;
 for(int i=0; i<n; i++){
  for(int j=i+1; j<n; j++){
   lines.emplace_back(v[i],v[j]);
  }
 }
 sort(lines.begin(),lines.end());
 for(line &l: lines){
  point p1= l.p1;
  point p2 = l.p2;
  int idx1 = mp[ {p1.x,p1.y}];
  int idx2 = mp[ {p2.x, p2.y}];
  //Do your work
  //Swap indexes
  v[idx1] = l.p2;
  v[idx2] = l.p1;
  mp[ {v[idx1].x, v[idx1].y}] = idx1;
  mp[ {v[idx2].x, v[idx2].y}] = idx2;
 }
}
