// 假设当前已经 横切 cntx 刀, 竖切 cnty 刀; 画图观察可得:
// 下一刀如果横切, 则增加的代价为 costx * (cnty + 1);
// 下一刀如果竖切, 则增加的代价为 costy * (cntx + 1);
// 为了让总花费最低，相同类型的操作应该将代价大的放前面。

// 那如果类型不同呢？考虑两个紧挨着的横切操作x和竖切操作y。
// 假设在这两刀之前，已经竖切 cnty 次，横切 cntx 次。
// 优先操作x时的代价为: (cnty+1)×costx+(cntx+2)×costy，
// 优先操作y时的代价为: (cntx+1)×costy+(cnty+2)×costx，
// 化简可得，优先操作x的前提是 costx > costy,
// 结论：无论是横切还是竖切，只需要优先操作代价大的就行。

// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

enum class state { x = 0, y };
struct data {
  state split; // state
  int cost;    // cost
};
bool desc(data &a, data &b) { return a.cost > b.cost; }

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  vec<data> a(n + m);
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d", &a[i].cost);
    a[i].split = state::x;
  }
  for (int i = n; i <= n + m - 2; i++) {
    scanf("%d", &a[i].cost);
    a[i].split = state::y;
  }

  sort(a.begin(), a.end(), desc);

  int cntx(0), cnty(0), total(0);
  for (auto e : a) {
    if (e.split == state::x) {
      cntx += 1, total += e.cost * (cnty + 1);
    } else {
      cnty += 1, total += e.cost * (cntx + 1);
    }
  }

  printf("%d\n", total);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}