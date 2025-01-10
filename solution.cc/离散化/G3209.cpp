// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <map>

using Hash = std::map<int, int>;

struct data {
  int l;
  int h;
  int r;
};

void UpdateHash(int t[], int k, Hash &hash) { hash[t[k]] = k; }

void UpdateByHash(int i, data a[], Hash &hash) {
  a[i].l = hash[a[i].l];
  a[i].r = hash[a[i].r];
}

const int N = 1e4;
// 离散化数值
void solve(void) {
  int n = 0;   // len of a
  int len = 0; // len of t
  data a[N + 1] = {};
  int t[2 * N + 1] = {}; // All Elements
  int f[2 * N + 1] = {}; // All Elements
  int l, r, h;
  while (scanf("%d %d %d", &l, &h, &r) != EOF) {
    n += 1;
    a[n] = {l, h, r};
    t[len + 1] = l;
    t[len + 2] = r;
    len += 2;
  }

  std::sort(t + 1, t + 1 + len);                   // 对元素升序排列
  len = std::unique(t + 1, t + 1 + len) - (t + 1); // 计算去重后的元素个数

  Hash hash; // H<K=Tval, V=Tindex>
  // Hash离散化, 更新原数字与离散化之后数字的关系
  for (int k = 1; k <= len; k++) {
    UpdateHash(t, k, hash);
  }
  for (int i = 1; i <= n; i++) {
    UpdateByHash(i, a, hash);
    for (int j = a[i].l; j < a[i].r; j++) {
      // 高度覆盖
      if (f[j] < a[i].h) {
        f[j] = a[i].h;
      }
    }
  }

  for (int i = 1; i <= len; i++) {
    if (f[i] != f[i - 1]) {
      // 存在高度差, 则输出
      printf("%d %d ", t[i], f[i]);
    }
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}