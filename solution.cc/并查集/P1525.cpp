// == Code Location ==
#include <algorithm>
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
  int x;
  int y;
  int c; // 冲突值
};

// 根据冲突值由大到小排序
bool desc(const node &a, const node &b) { return a.c > b.c; }

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  node a[m + 1];
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].c);
  }

  // 按冲突值降序排列
  std::sort(a + 1, a + 1 + m, desc);

  // 开两倍数组空间
  // DSU[1-n]存队友关系, DSU[n+1, 2n]存敌人关系
  quickunion::DSU dsu = quickunion::DSU(2 * n + 1);
  for (int i = 1; i <= m; i++) {
    auto [x, y, c] = a[i];
    if (dsu.is_connected(x, y)) {
      // 如果 <x, y>位于同一集合内,
      // 说明无法避免冲突, 集合分配已结束
      printf("%d\n", c);
      return;
    }
    // 敌人的敌人是朋友
    dsu.unionXY(x, y + n);
    dsu.unionXY(y, x + n);
  }

  // 若监狱无冲突, 输出0
  printf("%d\n", 0);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}