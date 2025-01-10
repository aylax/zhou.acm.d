// == Code Location ==
#include <cstdio>

int max4(int a, int b, int c, int d) {
  if (a < b)
    a = b;
  if (a < c)
    a = c;
  if (a < d)
    a = d;
  return a;
}

// 线性动态规划
const int N = 10;
int a[N][N];
int f[N][N][N][N];

int bestway(int i, int j, int x, int y) {
  int w1 = f[i - 1][j][x - 1][y];
  int w2 = f[i - 1][j][x][y - 1];
  int w3 = f[i][j - 1][x - 1][y];
  int w4 = f[i][j - 1][x][y - 1];
  return max4(w1, w2, w3, w4);
}
void solve(void) {
  int n;
  scanf("%d", &n);

  int x, y, i, j, k;
  while (scanf("%d %d %d", &x, &y, &k) != EOF) {
    if (x == 0 and y == 0 and k == 0) {
      break;
    }
    a[x][y] = k;
  }

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      for (x = 1; x <= n; x++) {
        for (y = 1; y <= n; y++) {
          k = bestway(i, j, x, y);
          f[i][j][x][y] = k + a[i][j] + a[x][y];
          if (i == x and j == y) { // 走相同格子, 只会加一次分
            f[i][j][x][y] -= a[i][j];
          }
        }
      }
    }
  }
  printf("%d\n", f[n][n][n][n]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}