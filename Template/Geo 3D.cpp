const double pi = 4 * atan(1);
const double eps = 1e-10;
inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double torad(double deg) { return deg / 180 * pi; }
struct Point{
 double x, y;
 Point (double x = 0, double y = 0): x(x), y(y) {}
 Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
 Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
 Point operator * (const double u) { return Point(x * u, y * u); }
 Point operator / (const double u) { return Point(x / u, y / u); }
 double operator * (const Point& u) { return x*u.y - y*u.x; }
};
struct Pt3D{
 double x, y, z;
 Pt3D() {}
 void read () {cin>>x>>y>>z;}
 void write () {cout<<x<<" --- "<<y<<" --- "<<z<<"\n";}
 Pt3D(double x, double y, double z) : x(x), y(y), z(z) {}
 Pt3D(const Pt3D &p) : x(p.x), y(p.y), z(p.z) {}
 Pt3D operator +(Pt3D b)  {return Pt3D(x+b.x,y+b.y, z+b.z);}
 Pt3D operator -(Pt3D b)  {return Pt3D(x-b.x,y-b.y, z-b.z);}
 Pt3D operator *(double b) {return Pt3D(x*b,y*b, z*b);}
 Pt3D operator /(double b) {return Pt3D(x/b,y/b, z/b);}
 bool operator  <(Pt3D b)  {return make_pair(make_pair(x,y),z) < make_pair(make_pair(b.x,b.y),b.z);}
 bool operator ==(Pt3D b)  {return dcmp(x-b.x)==0 && dcmp(y-b.y) == 0 && dcmp(z-b.z) == 0;}
};
typedef Pt3D Vector3D;
typedef vector<Point> Polygon;
typedef vector<Pt3D> Polyhedron;
namespace Vectorial{
 double getDot (Vector3D a, Vector3D b)  {return a.x*b.x+a.y*b.y+a.z*b.z;}
 Vector3D getCross(Vector3D a, Vector3D b) {return Pt3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);}
 double getLength (Vector3D a)   {return sqrt(getDot(a, a)); }
 double getPLength (Vector3D a)  {return getDot(a, a); }
 Vector3D unitVector(Vector3D v)   {return v/getLength(v);}
 double getUnsignedAngle(Vector3D u,Vector3D v){
  double cosTheta = getDot(u,v)/getLength(u)/getLength(v);
  cosTheta = max(-1.0,min(1.0,cosTheta));
  return acos(cosTheta);
 }
 Vector3D rotate(Vector3D v,Vector3D a,double rad){
  a = unitVector(a);
  return v * cos(rad) + a * (1 - cos(rad)) * getDot(a,v) + getCross(a,v) * sin(rad);
 }
}
struct Line3D{
 Vector3D v; Pt3D o;
 Line3D() {};
 Line3D(Vector3D v,Pt3D o):v(v),o(o){}
 Pt3D getPoint(double t) {return o + v*t;}
};
namespace Linear{
 using namespace Vectorial;
 double getDistSq(Line3D l, Pt3D p)    {return getPLength(getCross(l.v,p-l.o))/getPLength(l.v);}
 double getDistLinePoint(Line3D l, Pt3D p)   {return sqrt(getDistSq(l,p));}
 bool cmp(Line3D l,Pt3D p, Pt3D q)    {return getDot(l.v,p) < getDot(l.v,q);}
 Pt3D projection(Line3D l,Pt3D p)     {return l.o + l.v * getDot(l.v,p-l.o)/getPLength(l.v);}
 Pt3D reflection(Line3D l,Pt3D p)     {return projection(l,p)+projection(l,p)-p;}
 double getAngle(Line3D l,Line3D m)    {return getUnsignedAngle(l.v,m.v);}
 bool isParallel(Line3D p,Line3D q)    {return dcmp(getPLength(getCross(p.v,q.v))) == 0;}
 bool isPerpendicular(Line3D p,Line3D q)  {return dcmp(getDot(p.v,q.v)) == 0;}
 double getDist(Line3D l, Line3D m){
  Vector3D n = getCross(l.v, m.v);
  if(getPLength(n) == 0) return getDistLinePoint(l,m.o);
  else return fabs(getDot(m.o-l.o , n)) / getLength(n);
 }
 Pt3D getClosestPointOnLine1(Line3D l,Line3D m){
  Vector3D n = getCross(l.v, m.v);
  Vector3D n2 = getCross(m.v, n);
  return l.o + l.v * getDot(m.o-l.o, n2) / getDot(l.v, n2);
 }
}
struct Plane{
 Vector3D n; //normal n
 double d; //getDot(n,p) = d for any point p on the plane
 Plane() {}
 Plane(Vector3D n, double d) : n(n), d(d) {}
 Plane(Vector3D n, Pt3D p) : n(n), d(Vectorial :: getDot(n,p)) {}
 Plane(const Plane &p) : n(p.n), d(p.d) {}
};
namespace Planar{
 using namespace Vectorial;
 Plane getPlane(Pt3D a,Pt3D b,Pt3D c) {return Plane(getCross(b-a,c-a),a);}
 Plane translate(Plane p,Vector3D t)    {return Plane(p.n, p.d+getDot(p.n,t));}
 Plane shiftUp(Plane p,double dist)   {return Plane(p.n, p.d+dist*getLength(p.n));}
 Plane shiftDown(Plane p,double dist) {return Plane(p.n, p.d-dist*getLength(p.n));}
 double getSide(Plane p,Pt3D a)  {return getDot(p.n,a)-p.d;}
 double getDistance(Plane p,Pt3D a) {return fabs(getSide(p,a))/getLength(p.n);}
 Pt3D projection(Plane p,Pt3D a)   {return a-p.n*getSide(p,a)/getPLength(p.n);}
 Pt3D reflection(Plane p,Pt3D a)   {return a-p.n*getSide(p,a)/getPLength(p.n)*2;}
 bool intersect(Plane p, Line3D l, Pt3D& a){
  if(dcmp(getDot(p.n,l.v)) == 0) return false;
  a = l.o - l.v * getSide(p,l.o) / getDot(p.n,l.v);
  return true;
 }
 bool intersect(Plane p,Plane q,Line3D& l){
  l.v = getCross(p.n,q.n);
  if(dcmp(getPLength(l.v)) == 0) return false;
  l.o = getCross(q.n*p.d - p.n*q.d , l.v) / getPLength(l.v);
  return true;
 }
 double getAngle(Plane p,Plane q)   {return getUnsignedAngle(p.n,q.n);}
 bool isParallel(Plane p,Plane q)   {return dcmp(getPLength(getCross(p.n,q.n))) == 0;}
 bool isPerpendicular(Plane p,Plane q) {return dcmp(getDot(p.n,q.n)) == 0;}
 bool getAngle(Plane p,Line3D l)   {return pi/2.0 - getUnsignedAngle(p.n,l.v);}
 bool isParallel(Plane p,Line3D l)    {return dcmp(getDot(p.n,l.v)) == 0;}
 bool isPerpendicular(Plane p,Line3D l)  {return dcmp(getPLength(getCross(p.n,l.v))) == 0;}
 Line3D perpThrough(Plane p,Pt3D a)  {return Line3D(p.n,a);}
 Plane perpThrough(Line3D l,Pt3D a)  {return Plane(l.v,a);}
 //Modify p.n if necessary with respect to the reference point
 Vector3D rotateCCW90(Plane p,Vector3D d)  {return getCross(p.n,d);}
 Vector3D rotateCW90(Plane p,Vector3D d)   {return getCross(d,p.n);}
 pair<Pt3D, Pt3D> TwoPointsOnPlane(Plane p){
  Vector3D N = p.n; double D = p.d;
  assert(dcmp(N.x) != 0 || dcmp(N.y) != 0 || dcmp(N.z) != 0);
  if(dcmp(N.x) == 0 && dcmp(N.y) == 0) return {Pt3D(1,0,D/N.z), Pt3D(0,1,D/N.z)};
  if(dcmp(N.y) == 0 && dcmp(N.z) == 0) return {Pt3D(D/N.x,1,0), Pt3D(D/N.x,0,1)};
  if(dcmp(N.z) == 0 && dcmp(N.x) == 0) return {Pt3D(1,D/N.y,0), Pt3D(0,D/N.y,1)};
  if(dcmp(N.x) == 0) return {Pt3D(1,D/N.y,0), Pt3D(0,0,D/N.z)};
  if(dcmp(N.y) == 0) return {Pt3D(0,1,D/N.z), Pt3D(D/N.x,0,0)};
  if(dcmp(N.z) == 0) return {Pt3D(D/N.x,0,1), Pt3D(0,D/N.y,0)};
  if(dcmp(D)!=0) return {Pt3D(D/N.x,0,0), Pt3D(0,D/N.y,0)};
  return {Pt3D(N.y,-N.x,0), Pt3D(-N.y,N.x,0)};
 }
 Point From3Dto2D(Plane p, Pt3D a){
  assert( dcmp(getSide(p,a)) == 0 );
  auto Pair = TwoPointsOnPlane(p);
  Pt3D A = Pair.first;
  Pt3D B = Pair.second;
  Vector3D Z = p.n;     Z = Z / getLength(Z);
  Vector3D X = B - A;      X = X / getLength(X);
  Vector3D Y = getCross(Z,X);
  Vector3D v = a - A;
  assert( dcmp(getDot(v,Z)) == 0);
  return Point(getDot(v,X),getDot(v,Y));
 }
 Pt3D From2Dto3D(Plane p, Point a){
  auto Pair = TwoPointsOnPlane(p);
  Pt3D A = Pair.first;
  Pt3D B = Pair.second;
  Vector3D Z = p.n;     Z = Z / getLength(Z);
  Vector3D X = B - A;      X = X / getLength(X);
  Vector3D Y = getCross(Z,X);
  return A + X * a.x + Y * a.y;
 }
}
struct Sphere{
 Pt3D c;
 double r;
 Sphere() {}
 Sphere(Pt3D c, double r) : c(c), r(r) {}
 //Spherical cap with polar angle theta
 double Height(double alpha)   {return r*(1-cos(alpha));}
 double BaseRadius(double alpha)  {return r*sin(alpha);}
 double Volume(double alpha)   {double h = Height(alpha); return pi*h*h*(3*r-h)/3.0;}
 double SurfaceArea(double alpha) {double h = Height(alpha); return 2*pi*r*h;}
};
namespace Spherical{
 using namespace Vectorial;
 using namespace Planar;
 using namespace Linear;
 Sphere CircumscribedSphere(Pt3D a,Pt3D b,Pt3D c,Pt3D d){
  assert( dcmp(getSide(getPlane(a,b,c), d)) != 0);
  Plane U = Plane(a-b, (a+b)/2);
  Plane V = Plane(b-c, (b+c)/2);
  Plane W = Plane(c-d, (c+d)/2);
  Line3D l1,l2;
  bool ret1 = intersect(U,V,l1);
  bool ret2 = intersect(V,W,l2);
  assert(ret1 == true && ret2 == true);
  assert( dcmp(getDist(l1,l2)) == 0);
  Pt3D C = getClosestPointOnLine1(l1,l2);
  return Sphere(C, getLength(C-a));
 }
 pair<double,double> SphereSphereIntersection(Sphere s1,Sphere s2){
  double d = getLength(s1.c-s2.c);
  if(dcmp(d - s1.r -s2.r) >= 0) return {0,0};
  double R1 = max(s1.r,s2.r); double R2 = min(s1.r,s2.r);
  double y = R1 + R2 - d;
  double x = (R1*R1 - R2*R2 + d*d) / (2*d);
  double h1 = R1 - x;
  double h2 = y - h1;
  double Volume   = pi*h1*h1*(3*R1-h1)/3.0 + pi*h2*h2*(3*R2-h2)/3.0;
  double SurfaceArea = 2*pi*R1*h1 + 2*pi*R2*h2;
  return make_pair(SurfaceArea,Volume);
 }
 Pt3D getPointOnSurface(double r,double Lat,double Lon){
  Lat = torad(Lat);  //North-South
  Lon = torad(Lon);  //East-West
  return Pt3D(r*cos(Lat)*cos(Lon), r*cos(Lat)*sin(Lon), r*sin(Lat));
 }
 int intersect(Sphere s,Line3D l, vector<Pt3D>& ret){
  double h2 = s.r*s.r - getDistSq(l,s.c);
  if(dcmp(h2)<0) return 0;
  Pt3D p = projection(l,s.c);
  if(dcmp(h2) == 0) {ret.push_back(p); return 1;}
  Vector3D h = l.v * sqrt(h2) / getLength(l.v);
  ret.push_back(p-h); ret.push_back(p+h); return 2;
 }
 double GreatCircleDistance(Sphere s,Pt3D a,Pt3D b){
  return s.r * getUnsignedAngle(a-s.c, b-s.c);
 }
}
namespace Poly{
 using namespace Vectorial;
 Sphere SmallestEnclosingSphere(Polyhedron p){
  int n = p.size();
  Pt3D C(0,0,0);
  for(int i=0; i<n; i++) C = C + p[i];
  C = C / n;
  double P = 0.1;
  int pos = 0;
  int Accuracy = 70000;
  for (int i = 0; i < Accuracy; i++) {
   pos = 0;
   for (int j = 1; j < n; j++){
    if(getPLength(C - p[j]) > getPLength(C - p[pos])) pos = j;
   }
   C = C + (p[pos] - C)*P;
   P *= 0.998;
  }
  return Sphere(C, getPLength(C - p[pos]));
 }
}
