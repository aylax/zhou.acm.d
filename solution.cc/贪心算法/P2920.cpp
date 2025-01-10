// == Code Location ==
#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

struct data {
  int s; // 最迟完成时刻
  int t; // 工作耗时
};

bool compare(data &a, data &b) { return a.s > b.s; }

void solve(void) {
  int n;
  scanf("%d", &n);

  vec<data> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &a[i].t, &a[i].s);
  }

  std::sort(a.begin(), a.end(), compare);

  int r = INT_MAX; // 最迟开始时刻
  for (auto [s, t] : a) {
    r = std::min<int>(s, r) - t;
    if (r < 0) { r = -1; break; }
  }

  printf("%d", r);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}