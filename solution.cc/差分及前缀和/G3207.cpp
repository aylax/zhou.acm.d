// == Code Location ==
#include <cstdio>

void solve(void) {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  int a[n + 1][m + 1] = {};
  int s[n + 1][m + 1] = {};
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      s[i][j] = s[i][j - 1] + s[i - 1][j];
      s[i][j] += a[i][j] - s[i - 1][j - 1];
    }
  }

  int x, y, maxt = -1e9;
  for (int i = 1; i + k <= n + 1; i++) {
    for (int j = 1; j + k <= m + 1; j++) {
      int t = s[i + k - 1][j + k - 1] + s[i - 1][j - 1];
      t = t - s[i - 1][j + k - 1] - s[i + k - 1][j - 1];
      if (t > maxt) {
        maxt = t, x = i, y = j;
      }
    }
  }

  printf("%d %d", x, y);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}