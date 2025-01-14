// == Code Location ==
#include <algorithm>
#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

struct node {
  int t; // 投入时间
  int s; // 延长时间
  int h; // 叠加高度
};

// 按照投入时间比较元素
bool asc(const node &a, const node &b) { return a.t < b.t; }

// 0-1背包问题
// 转移方程: 时间复杂度 O(n*m)
// F(i, j)表示: i个垃圾, 累计高度j, 最久存活时间
// 第i个垃圾分为 吃 | 不吃 两种情况
// F[i][j] = Max(F[i-1][j] + A[i].s, F[i-1][j-A[i].h])
void solve(void) {
  int m; // 总时长(m)
  int n; // 总数量(n)
  scanf("%d %d", &m, &n);

  node a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &a[i].t, &a[i].s, &a[i].h);
  }

  // 按照投入时间排序
  std::sort(a + 1, a + n + 1, asc);

  int f[m + 1] = {10}; // 最久存活时间
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= 0; j--) {
      // 如果最久存活时间小于刻的垃圾投放
      if (f[j] < a[i].t) {
        continue;
      }
      // 如果已经到井口, 就结束计算,并输出时刻
      if (a[i].h + j >= m) {
        printf("%d\n", a[i].t);
        return;
      }

      // 不吃的情况下, 需要更新: 叠加高度下的最久存活时间 Max(F[j+h], F[j])
      f[j + a[i].h] = max(f[j + a[i].h], f[j]);
      // 当前高度下的最久存活时间增加
      f[j] += a[i].s;
    }
  }
  printf("%d\n", f[0]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}