// == Code Location ==
#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

// 0-1背包问题
// 转移方程: 时间复杂度 O(n*m*m)
// F(i, j)表示: i道料理, 累计耗时j, 所能产生的最大价值
// F[i][j] = Max(F[i-1][j-k*w[i]]+k*v[i], F[i-1][j])
// 其中, 1 <= k*w[i] <= j
void solve(void) {
  int h0, m0, h1, m1;
  scanf("%d:%d", &h0, &m0);
  scanf("%d:%d", &h1, &m1);

  int m; // 总时长(m)
  m = (h1 - h0) * 60 + (m1 - m0);

  int n; // 总数量(n)
  scanf("%d", &n);

  int w[n + 1] = {};             // 耗时(w)
  int v[n + 1] = {};             // 价值(v)
  int c[n + 1] = {};             // 可用次数(c)[0代表无数次]
  for (int i = 1; i <= n; i++) { // loop scanf
    scanf("%d %d %d", &w[i], &v[i], &c[i]);
  }

  int f[m + 1] = {}; // 耗时m, 所能产生的最大价值
  for (int i = 1; i <= n; i++) {
    int maxk = c[i]; // 使用次数
    if (maxk == 0) {
      maxk = m;
    } // 0表示无上限次数(实际最多m次)

    for (int j = m; j >= w[i]; j--) {
      for (int k = 1; k <= maxk; k++) {
        int kwi = k * w[i];
        if (kwi > j) {
          break;
        }
        int kvi = k * v[i];
        f[j] = max(f[j - kwi] + kvi, f[j]);
      }
    }
  }
  printf("%d\n", f[m]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}