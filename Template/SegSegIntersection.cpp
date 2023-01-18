inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
bool is_point_on_seg(PT a, PT b, PT p) {
 if (fabs(cross(p - b, a - b)) < eps) {
  if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
  if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
  return true;
 }
 return false;
}
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
 double oa = cross2(c, d, a), ob = cross2(c, d, b);
 double oc = cross2(a, b, c), od = cross2(a, b, d);
 if (oa * ob < 0 && oc * od < 0){
  ans = (a * ob - b * oa) / (ob - oa);
  return 1;
 }
 else return 0;
}
set<PT> seg_seg_intersection_inside(PT a,  PT b,  PT c,  PT d) {
 PT ans;
 if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
 set<PT> se;
 if (is_point_on_seg(c, d, a)) se.insert(a);
 if (is_point_on_seg(c, d, b)) se.insert(b);
 if (is_point_on_seg(a, b, c)) se.insert(c);
 if (is_point_on_seg(a, b, d)) se.insert(d);
 return se;
}
