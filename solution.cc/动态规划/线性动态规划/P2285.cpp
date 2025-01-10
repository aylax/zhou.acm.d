// == Code Location ==
#include <cstdio>

int abs(int a) { return a > 0 ? 0 + a : 0 - a; }

int max(int a, int b) { return a > b ? a : b; }

void assign(int xs[], int l, int r, int x) {
  for (int i = l; i <= r; i++) {
    xs[i] = x;
  }
}

int d(int a, int b) { return abs(a - b); }
// 线性动态规划
void solve(void) {
  int m, n; // 宽, 数量
  scanf("%d %d", &m, &n);

  int t[n + 1] = {};
  int x[n + 1] = {};
  int y[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &t[i], &x[i], &y[i]);
  }

  int f[n + 1]; // 初始化
  assign(f, 0, n, 1);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      int dx = d(x[i], x[j]);
      int dy = d(y[i], y[j]);
      if ((dx + dy) <= (t[i] - t[j])) { // check
        f[i] = max(f[j] + 1, f[i]);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    f[0] = max(f[i], f[0]);
  }
  printf("%d\n", f[0]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}