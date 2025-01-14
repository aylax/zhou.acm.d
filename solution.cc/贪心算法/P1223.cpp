// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

struct data {
  int k;
  int t;
};

bool asc(data &a, data &b) { return a.t < b.t; }

void solve(void) {
  int n;
  scanf("%d", &n);

  vec<data> a(n);
  for (int i = 0; i < n; i++) {
    a[i].k = i + 1;
    scanf("%d", &a[i].t);
  }

  std::sort(a.begin(), a.end(), asc);

  int tot = 0, i = 0;
  for (auto [k, t] : a) {
    printf("%d ", k);
    tot += t * (n - 1 - i);
    i += 1;
  }

  double ans = tot * 1.0 / n;
  printf("\n%.2lf\n", ans);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}