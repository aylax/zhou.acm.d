// == Code Location ==
#include <cstdio>

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  int d[n + 1][n + 2] = {}; // 构建差分数组
  int x1, y1, x2, y2;       // (x1, y1) (x2, y2)
  for (int j = 1; j <= m; j++) {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    // 差分数组按行处理
    for (int i = x1; i <= x2; i++) {
      d[i][y1] += 1;
      d[i][y2 + 1] -= 1;
    }
  }

  for (int i = 1; i <= n; i++) {
    int num = 0;
    for (int j = 1; j <= n; j++) {
      num += d[i][j];
      printf("%d ", num);
    }
    printf("\n");
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}