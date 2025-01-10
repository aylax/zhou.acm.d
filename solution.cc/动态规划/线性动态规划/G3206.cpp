// == Code Location ==
#include <cstdio>

// 线性动态规划 复杂度 O(n^2)
// f[i][d] 表示以第i个数字结尾, 差值为d的子序列的累计方案数
const int m = 2e4 + 5;   // 偏移值, 处理负数
const int p = 998244353; // mod p
int f[1005][2 * m];
void solve(void) {
  int n; // 数量
  scanf("%d", &n);

  int a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  int sum = n; // 单个元素也是和谐的
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      int k = a[i] - a[j] + m;
      // 累加原来的所有方案数
      sum = (sum + f[j][k] + 1) % p;
      f[i][k] = (f[i][k] + f[j][k] + 1) % p;
    }
  }

  printf("%d\n", sum);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}