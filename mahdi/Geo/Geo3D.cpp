

struct Point3D {
  Ti x, y, z;
  Point3D(Ti x = 0, Ti y = 0, Ti z = 0) : x(x), y(y), z(z) {}

  Point3D operator + (const Point3D& u) const { return Point3D(x + u.x, y + u.y, z+u.z); }
  Point3D operator - (const Point3D& u) const { return Point3D(x - u.x, y - u.y, z-u.z); }
  Point3D operator * (const long long u) const { return Point3D(x * u, y * u, z*u); }
  Point3D operator * (const Tf u) const { return Point3D(x * u, y * u, z*u); }
  Point3D operator / (const Tf u) const { return Point3D(x / u, y / u, z/u); }

  bool operator == (const Point3D& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z) == 0; }
  bool operator != (const Point3D& u) const { return !(*this == u); }
  bool operator < (const Point3D& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0) || (dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z) < 0); }
  friend istream &operator >> (istream &is, Point3D &p) { return is >> p.x >> p.y >> p.z; }
  friend ostream &operator << (ostream &os, const Point3D &p) { return os << "("<<p.x << " " << p.y << " " << p.z<<")"; }
};

Ti dot(Point3D a, Point3D b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Tf length(Point3D a) { return sqrt((Tf)dot(a, a)); }

Tf angle(Point3D a, Point3D b) { return acos(dot(a, b) / length(a) / length(b)); }
Point3D unit(Point3D a) { return a / length(a); }

struct Sphere{
    Point3D c;
    Tf r;
    Sphere(Point3D c=0, double r=0) : c(c), r(r) {}

	// return -1 if inside, 0 if on surface, 1 if outside
	int check(Point3D p) { return dcmp(length(p - c) - r); }

    //Spherical cap with polar angle theta
    Tf Height(Tf alpha)      {return r*(1-cos(alpha));}
    Tf BaseRadius(Tf alpha)  {return r*sin(alpha);}
    Tf Volume(Tf alpha)      {Tf h = Height(alpha); return PI*h*h*(3*r-h)/3.0;}
    Tf SurfaceArea(Tf alpha) {Tf h = Height(alpha); return 2*PI*r*h;}
	bool operator <(const Sphere &s) const { return r > s.r; }
	bool operator == (const Sphere &s) const { return c == s.c && dcmp(r - s.r) == 0; }
	friend istream &operator >> (istream &is, Sphere &p) { return is >> p.c >> p.r; }
	friend ostream &operator << (ostream &os, const Sphere &p) { return os << "("<<p.c << " " << p.r<<")"; }
};