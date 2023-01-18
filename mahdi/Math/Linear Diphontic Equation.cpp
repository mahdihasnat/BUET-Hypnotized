int gcd(int a, int b, int &x, int &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m){
  long double x;  uint64_t c; int64_t r;
  if (a >= m) a %= m; if (b >= m) b %= m;
  x = a;  c = x * b / m;
  r = (int64_t)(a * b - c * m) % (int64_t)m;
  return r < 0 ? r + m : r;
}
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g)
{
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g)
    {
        return false;
    }
    long long dx = c / a;
    c -= dx * a;
    long long dy = c / b;
    c -= dy * b;
    x0 = dx + mul_mod(x0, c / g, b);
    y0 = dy + mul_mod(y0, c / g, a);
    if (a < 0)
        x0 = -x0;
    if (b < 0)
        y0 = -y0;
    return true;
}
