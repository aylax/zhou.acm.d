// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <map>

using i64 = long long;

using Hash = std::map<int, int>;

void UpdateTable(int t[], int ri[4], int len) {
  for (int j = 0; j < 4; j++) {
    t[len + j + 1] = ri[j];
  }
}

void UpdateHash(int t[], int k, Hash &h) { h[t[k]] = k; }

void UpdateByHash(int ri[4], Hash &h) {
  for (int j = 0; j < 4; j++) {
    ri[j] = h[ri[j]];
  }
}

// 离散化数据 + 差分数组
// 矩形对角坐标: d[(0, 5), (4, 1)]
// 对角坐标转换: d[(1, 0), (5, 1)]
void solve(void) {
  int n;
  scanf("%d", &n);

  int len = 0;                      // 数组T中的元素数量
  int r[n + 1][4] = {};             // 对角矩阵[X1, X2, Y1, Y2]
  int t[n * 4 + 1] = {};            // 存储所有坐标数字
  int d[n * 4 + 1][n * 4 + 1] = {}; // 二维差分矩阵
  int a[n * 4 + 1][n * 4 + 1] = {}; // 二维前缀和矩阵
  for (int i = 1; i <= n; i++) {
    // 笛卡尔坐标 -> 数组行列
    scanf("%d %d", &r[i][1], &r[i][2]); // [Y1, X2]
    scanf("%d %d", &r[i][3], &r[i][0]); // [Y2, X1]
    UpdateTable(t, r[i], len);
    len = len + 4;
  }

  std::sort(t + 1, t + 1 + len); // 对元素升序排列

  len = std::unique(t + 1, t + 1 + len) - (t + 1); // 计算去重后的元素个数

  Hash h; // h<K=Tval, V=Tindex>
  // Hash离散化, 更新原数字与离散化之后数字的关系
  for (int k = 1; k <= len; k++) {
    UpdateHash(t, k, h);
  }
  for (int i = 1; i <= n; i++) {
    UpdateByHash(r[i], h);
  }

  // 二维差分矩阵上统计覆盖区域
  // r[i]中存的是坐标值在数组T中的下标
  // 参考[前缀和数组求区域面积的公式]
  // 注意: X2,Y2位置取不到
  for (int i = 1; i <= n; i++) {
    auto [X1, Y1, X2, Y2] = r[i];
    d[X2][Y2] += 1;
    d[X1][Y2] -= 1;
    d[X2][Y1] -= 1;
    d[X1][Y1] += 1;
  }

  // 差分数组还原元素
  for (int i = 1; i < len; i++) {
    for (int j = 1; j < len; j++) {
      a[i][j] = a[i - 1][j] + a[i][j - 1];
      a[i][j] += d[i][j] - a[i - 1][j - 1];
    }
  }

  i64 ret = 0;
  for (int i = 1; i < len; i++) {
    for (int j = 1; j < len; j++) {
      if (a[i][j] > 0) { // check
        i64 a = t[i + 1] - t[i];
        i64 b = t[j + 1] - t[j];
        ret += (a * b);
      }
    }
  }

  printf("%lld", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}