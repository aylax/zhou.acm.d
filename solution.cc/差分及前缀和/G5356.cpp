// == Code Location ==
#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }

// 差分数组
void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  int a[n + 1] = {};
  int q[m + 1][3] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  for (int j = 1; j <= m; j++) {
    scanf("%d %d %d", &q[j][0], &q[j][1], &q[j][2]);
  }

  int d[n + 1] = {}; // 构建差分数组
  int l, r, val;
  for (int j = 1; j <= m; j++) {
    l = q[j][0], r = q[j][1], val = q[j][2];
    d[l] += val;
    d[r + 1] -= val;
  }

  int k; // 累计的差值
  int ans = 1e9;
  for (int i = 1; i <= n; i++) {
    k += d[i];
    a[i] += k;
    ans = min(ans, a[i]);
  }
  printf("%d", ans);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}