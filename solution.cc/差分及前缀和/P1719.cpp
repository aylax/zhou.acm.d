// == Code Location ==
#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

// 二维前缀和
void solve(void) {
  int n;
  scanf("%d", &n);
  int a[n + 1][n + 1] = {};
  int s[n + 1][n + 1] = {};
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
      s[i][j] = s[i][j - 1] + s[i - 1][j];
      s[i][j] += a[i][j] - s[i - 1][j - 1];
    }
  }

  int ans = s[1][1];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int x = i; x <= n; x++) {
        for (int y = j; y <= n; y++) {
          int p = s[x][y] + s[i - 1][j - 1];
          p = p - s[x][j - 1] - s[i - 1][y];
          ans = max(ans, p);
        }
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}