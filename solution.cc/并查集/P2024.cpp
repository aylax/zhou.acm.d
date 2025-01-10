// == Code Location ==
#include <cstdio>
#include <numeric>
#include <vector>

template <typename T> using vec = std::vector<T>;

// 基于数组的快速修改并查集实现
namespace quickunion { // 通过树形结构描述节点间的关系
struct DSU {       // 时间复杂度: 查询 O(logn * n), 修改 O(logn * n)
  vec<int> parent; // 数组索引表示元素编号, 存储父节点的编号
  vec<int> depth;  // 当前元素所处集合的深度

  DSU(int n) {          // 初始化时, 每个元素本身构成一个集合
    depth.assign(n, 1); // 初始层级深度深度全部为1
    parent.resize(n);   // 分配内存空间
    std::iota(parent.begin(), parent.end(), 0); // 递增赋值
  }

  int size() { return parent.size(); }

  // 查找元素x所在的集合编号
  int find(int p) { // 反复查找父级节点
    if (parent[p] != p) {
      parent[p] = find(parent[p]);
    }
    return parent[p];
  }

  // 判断元素x和元素y是否属于同一集合
  bool is_connected(int x, int y) { return find(x) == find(y); }

  // 将归并两个元素的集合
  void unionXY(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
      return;
    }

    // 将层级深度较小的集合,
    // 合并到层级深度较大的集合中
    if (depth[xroot] < depth[yroot]) {
      parent[xroot] = yroot; // x的根节点指向y的根节点
    } else if (depth[xroot] > depth[yroot]) {
      parent[yroot] = xroot;
    } else { // 层级深度相同情况下进行合并, 增加一层
      parent[yroot] = xroot;
      depth[xroot] += 1;
    }
  }
};
} // namespace quickunion

struct node {
  int p;
  int x;
  int y;
};

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  node a[m + 1];

  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &a[i].p, &a[i].x, &a[i].y);
  }

  int ret = 0;
  // Y(同类)[1-n], Y(食物)[n+1, 2n], Y(天敌)[2n+1, 3n]
  quickunion::DSU dsu = quickunion::DSU(3 * n + 1);
  for (int i = 1; i <= m; i++) {
    auto [p, x, y] = a[i];

    // 鉴别谎言
    bool lie01 = (x > n or y > n);

    if (lie01) {
      ret += 1;
      continue; // 必须要加continue
    }
    // xy之间可能存在的关系
    // Y(同类)[1-n], Y(食物)[n+1, 2n], Y(天敌)[2n+1, 3n]
    bool r1 = dsu.is_connected(x, y);         // y的同类
    bool r2 = dsu.is_connected(x, y + n);     // y的食物
    bool r3 = dsu.is_connected(x, y + 2 * n); // y的天敌

    // 鉴别谎言
    bool lie02 = (p == 1 and (r2 or r3));
    bool lie03 = (p == 2 and (r1 or r2));

    // 食物链: A -> B -> C -> A
    if (lie02 or lie03) {
      ret += 1;
    } else if (p == 1) {
      dsu.unionXY(x, y);
      dsu.unionXY(x + n, y + n);
      dsu.unionXY(x + 2 * n, y + 2 * n);
    } else if (p == 2) {
      dsu.unionXY(x, y + 2 * n);
      dsu.unionXY(x + n, y);
      dsu.unionXY(x + 2 * n, y + n);
    } else {
    }
  }
  printf("%d\n", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}