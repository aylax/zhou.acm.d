// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

struct data {
  int p; // price
  int q; // amount
};

bool compare(data &a, data &b) { return a.p < b.p; }

void solve(void) {
  int s, n;
  scanf("%d %d", &s, &n);

  vec<data> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &a[i].p, &a[i].q);
  }

  std::sort(a.begin(), a.end(), compare);

  int tot = 0;
  for (auto [p, q] : a) {
    if (not(s > 0)) { break; }
    int k = (s > q) ? q : s;
    s -= k, tot += p * k;
  }
  printf("%d\n", tot);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}
