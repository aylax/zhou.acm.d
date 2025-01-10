// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <vector>

using i64 = long long;

template <typename T> using vec = std::vector<T>;

void solve(void) {
  int n;
  scanf("%d", &n);

  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  std::sort(a.begin(), a.end());

  i64 sum = 0;
  int l = 0, r = n - 1;
  for (; l < r; l += 1, r -= 1) {
    sum += 1LL * (a[r] - a[l]);
  }
  printf("%lld\n", sum);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}