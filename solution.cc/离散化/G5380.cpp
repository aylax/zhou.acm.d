// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <map>

using i64 = long long;

int max(int a, int b) { return a > b ? a : b; }

struct interval {
  int l;
  int r;
};

bool asc(interval a, interval b) {
  if (a.l == b.l) {
    return a.r < b.r;
  } else {
    return a.l < b.l;
  }
}

// 端点区间合并 260
void solve0(void) {
  int n;
  scanf("%d", &n);
  interval a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &a[i].l, &a[i].r);
  }

  std::sort(a + 1, a + 1 + n, asc);

  i64 len = 0; // 修补长度
  interval tmp = a[1];
  for (int i = 2; i <= n; i++) {
    // 如果能右端点和左端点重叠就合并区间
    if (tmp.r >= a[i].l) {
      tmp.r = max(a[i].r, tmp.r);
    } else { // 否则更新len
      len += 1LL * tmp.r - tmp.l;
      tmp = a[i]; // 重置tmp
    }
  }

  len += 1LL * tmp.r - tmp.l;
  printf("%lld\n", len);
}

// -------------------------------------------------------------
using Hash = std::map<int, int>;

// 离散化数值
void solve1(void) {
  int n;
  scanf("%d", &n);

  int len = 0;                   // len of t
  int l[n + 1] = {};             // Left Interval
  int r[n + 1] = {};             // Right Interval
  int t[2 * n + 1] = {};         // All Elements
  for (int i = 1; i <= n; i++) { // loop scanf
    scanf("%d %d", &l[i], &r[i]);
    t[len + 1] = l[i];
    t[len + 2] = r[i];
    len += 2;
  }

  std::sort(t + 1, t + 1 + len);                   // 对元素升序排列
  len = std::unique(t + 1, t + 1 + len) - (t + 1); // 计算去重后的元素个数

  Hash h; // h<K=Tval, V=Tindex>
  // Hash离散化, 更新原数字与离散化之后数字的关系
  for (int k = 1; k <= len; k++) {
    h[t[k]] = k;
  }
  for (int i = 1; i <= n; i++) {
    l[i] = h[l[i]];
    r[i] = h[r[i]];
  }

  int f[2 * n + 1] = {};
  for (int i = 1; i <= n; i++) {
    for (int j = l[i]; j < r[i]; j++) {
      f[j] = 1;
    }
  }

  i64 ret = 0;
  for (int i = 1; i <= len; i++) {
    if (f[i] > 0) {
      ret += 1LL * t[i + 1] - t[i];
    }
  }

  printf("%lld", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve0();
  fclose(stdin);
  return 0;
}