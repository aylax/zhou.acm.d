// == Code Location ==
#include <cstdio>

using i64 = long long;

i64 max(i64 a, i64 b) { return a > b ? a : b; }

// 0-1背包问题
// 转移方程: 时间复杂度 O(n*m)
// F(i, j)表示: i株草药, 累计耗时j, 所能产生的最大价值
// F[i][j] = Max(F[i-1][j-w[i]] + v[i], F[i-1][j])
void solve(void) {
  int m; // 总时长(m)
  int n; // 总数量(n)
  scanf("%d %d", &m, &n);

  int w[n + 1] = {}; // 耗时(w)
  int v[n + 1] = {}; // 价值(v)
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &w[i], &v[i]);
  }

  i64 f[m + 1] = {}; // 耗时m, 所能产生的最大价值
  for (int i = 1; i <= n; i++) {
    for (int j = w[i]; j <= m; j++) { // 无限采草药
      f[j] = max(f[j - w[i]] + v[i], f[j]);
    }
  }
  printf("%lld\n", f[m]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}