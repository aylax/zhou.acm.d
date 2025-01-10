// == Code Location ==
#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

struct node {
  int w;
  int v;
};

// 0-1背包问题
// 转移方程: 时间复杂度 O(n*m)
// F(i, j)表示: i个物品, 累计花费j, 所能产生的最大价值
// 其中, 优先计算主件影响力, 再将附件的影响力合并到主件中
// F[i][j] = Max(F[i-1][j-w[i]] + v[i], F[i-1][j])
void solve(void) {
  int m, n; // 总额度(m) 总数量(n)
  scanf("%d %d", &m, &n);

  node main[n + 1] = {};    // main
  node part[n + 1][3] = {}; // part of main

  int ord;     // 附件在主件中的插槽位置(Ord)
  int w, v, r; // 价格(w), 价值(v), Root(r)

  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &w, &v, &r);
    if (r == 0) { // 主件
      main[i].w = w;
      main[i].v = w * v;
    } else { // 附件
      // 附件放入主件的对应插槽
      part[r][0].w += 1;
      ord = part[r][0].w;
      part[r][ord].w = w;
      part[r][ord].v = w * v;
    }
  }

  int f[m + 1] = {};
  for (int i = 1; i <= n; i++) {
    for (int j = m; main[i].w > 0 and j >= main[i].w; j--) {
      f[j] = max(f[j], f[j - main[i].w] + main[i].v); // 考虑无附件情况
      if (j >= main[i].w + part[i][1].w) {            // 附件1
        w = main[i].w + part[i][1].w;
        v = main[i].v + part[i][1].v;
        f[j] = max(f[j], f[j - w] + v);
      }
      if (j >= main[i].w + part[i][2].w) { // 附件2
        w = main[i].w + part[i][2].w;
        v = main[i].v + part[i][2].v;
        f[j] = max(f[j], f[j - w] + v);
      }
      if (j >= main[i].w + part[i][1].w + part[i][2].w) { // 附件1+附件2
        w = main[i].w + part[i][1].w + part[i][2].w;
        v = main[i].v + part[i][1].v + part[i][2].v;
        f[j] = max(f[j], f[j - w] + v);
      }
    }
  }
  printf("%d\n", f[m]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}