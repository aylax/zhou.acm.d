// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <map>

using Hash = std::map<int, int>;

struct data {
  int id;
  int x;
};

bool contains(Hash &h, int key) { return h.find(key) != h.end(); }

bool asc(data a, data b) { return a.x < b.x; }

// 离散化ID + 双端队列
void solve(void) {
  int n;
  scanf("%d", &n);

  Hash h;             // h<K=ID, V=Number>
  data a[n + 1] = {}; // Left Interval

  int x, id;
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &x, &id);
    a[i] = {id, x};
    if (!contains(h, id)) {
      h[id] = 0;
    }
  }

  std::sort(a + 1, a + 1 + n, asc); // 对元素升序排列

  int ret = 1e9;
  int head = 1;                // head
  int cnt = 0, len = h.size(); // 当前入队种类, 奶牛种类
  for (int i = 1; i <= n; i++) {
    int id1 = a[i].id;
    h[id1] += 1;
    if (h[id1] == 1) {
      cnt += 1;
    } // 新品种奶牛
    while (cnt == len) { // 所有奶牛都入队时
      ret = std::min(ret, a[i].x - a[head].x);
      int id0 = a[head].id;
      h[id0] -= 1;
      if (h[id0] == 0) {
        cnt -= 1;
      } // 剔除该种类
      head += 1;
    }
  }
  printf("%d", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}