// == Code Location ==
#include <cstdio>

using i64 = long long;

i64 min(i64 a, i64 b) { return a < b ? a : b; }

i64 abs(i64 a) { return a > 0 ? 0 + a : 0 - a; }

struct data {
  int w;
  int v;
};

struct interval {
  int l;
  int r;
};

i64 sumof(data a[], interval g[], int n, int m, int w) {
  int snum[n + 1] = {}; // 满足条件的元素个数 (前缀和)
  i64 sval[n + 1] = {}; // 满足条件的元素价值 (前缀和)

  // 预处理计算前缀和
  for (int i = 1; i <= n; i++) {
    snum[i] = snum[i - 1];
    sval[i] = sval[i - 1];
    if (a[i].w >= w) {
      snum[i] += 1;
      sval[i] += a[i].v;
    }
  }

  int l, r; // 单次检测的区间[L, R]
  int dnum; // 区间内的符合条件元素的累计数量
  i64 dval; // 区间内的符合条件元素的累计价值

  i64 sum = 0;
  for (int j = 1; j <= m; j++) {
    l = g[j].l, r = g[j].r;
    dnum = snum[r] - snum[l - 1];
    dval = sval[r] - sval[l - 1];
    sum += (dnum * dval);
  }

  return sum;
}

// 前缀和预处理数据 + 二分查找W
void solve(void) {
  int n, m; // 矿石个数 n, 区间个数 m
  i64 k;    // 标准值 k
  scanf("%d %d %lld", &n, &m, &k);

  int l = 0, r = -1; // 区间 [L, R]
  data a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &a[i].w, &a[i].v);
    if (r < a[i].w) {
      r = a[i].w;
    }
  }

  interval g[m + 1] = {};
  for (int j = 1; j <= m; j++) {
    scanf("%d %d", &g[j].l, &g[j].r);
  }

  i64 ans = 1e12 + 5;
  while (l <= r) {
    int mid = (l + r) / 2;
    i64 sum = sumof(a, g, n, m, mid);
    if (sum == k) {
      printf("%lld\n", 0LL);
      return;
    }
    if (sum < k) {
      r = mid - 1;
    }
    if (sum > k) {
      l = mid + 1;
    }
    ans = min(ans, abs(sum - k));
  }
  printf("%lld\n", ans);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}