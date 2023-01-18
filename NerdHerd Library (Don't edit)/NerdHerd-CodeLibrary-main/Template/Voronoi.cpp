const Tf INF = 1e10;
vector<Polygon> voronoi(vector<PT> site, Tf bsq) {
  int n = site.size();
  vector<Polygon> region(n);
  PT A(-bsq, -bsq), B(bsq, -bsq),
  C(bsq, bsq), D(-bsq, bsq);
  for(int i = 0; i < n; ++i) {
    vector<DirLine> li(n - 1);
    for(int j = 0, k = 0; j < n; ++j) {
      if(i == j) continue;
      li[k++] = DirLine((site[i] + site[j]) / 2,
      rotate90(site[j] - site[i]));
    }
    li.emplace_back(A,B-A); li.emplace_back(B,C-B);
    li.emplace_back(C,D-C); li.emplace_back(D,A-D);
    region[i] = halfPlaneIntersection(li);
  }
  return region;
}
