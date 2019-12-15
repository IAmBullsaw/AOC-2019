class Point {
 public:
  Point(long long x, long long y);

  long long X() const;
  long long Y() const;

  void X(long long const& x);
  void Y(long long const& y);

 private:
  long long x;
  long long y;
};
