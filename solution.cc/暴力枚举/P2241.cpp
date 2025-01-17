// == Code Location ==
#include <cstdio>

using i64 = long long;

i64 min(i64 a, i64 b) { return a < b ? a : b; }

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  i64 rect(0LL), square(0LL);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      rect += (i * j);
      square += min(i, j);
    }
  }

  printf("%lld %lld", square, rect - square);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}