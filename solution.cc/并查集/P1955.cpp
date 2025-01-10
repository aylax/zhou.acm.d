// == Code Location ==
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <unordered_map>
#include <vector>

using Hash = std::unordered_map<int, int>;
template <typename T> using vec = std::vector<T>;

// 基于数组的快速修改并查集实现
namespace quickunion { // 通过树形结构描述节点间的关系
struct DSU {       // 时间复杂度: 查询 O(logn * n), 修改 O(logn * n)
  vec<int> parent; // 数组索引表示元素编号, 存储父节点的编号
  vec<int> depth;  // 当前元素所处的层级深度

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

const int MAXN = 1e5 + 5;
struct node {
  int p;
  int x;
  int y;
};

node a[MAXN];    // 原始数据
int b[MAXN * 2]; // 离散化数据

bool compare(node &a, node &b) { return a.p > b.p; }

void UpdateHash(int k, Hash &hash) { hash[b[k]] = k; }

void UpdateByHash(int i, Hash &hash) {
  a[i].x = hash[a[i].x];
  a[i].y = hash[a[i].y];
}

// 先将p==1的所有关系录入
// 再判断p!=1时的关系, 简化并差集空间
void solveOnce() {
  int m;
  scanf("%d", &m);

  int x, y, p, n = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &x, &y, &p);
    a[i] = {p, x, y};
    b[n + 1] = x;
    b[n + 2] = y;
    n += 2;
  }

  // 计算去重后的元素个数
  std::sort(b + 1, b + 1 + n);
  n = std::unique(b + 1, b + 1 + n) - (b + 1);

  // Hash离散化, 更新原数字与离散化之后数字的关系
  Hash hash;
  for (int k = 1; k <= n; k++) {
    UpdateHash(k, hash);
  }
  for (int i = 1; i <= m; i++) {
    UpdateByHash(i, hash);
  }

  // [1, n] 相等域;
  quickunion::DSU dsu = quickunion::DSU(n + 1);

  // 将相等的判定(p==1)放在前面
  std::sort(a + 1, a + 1 + m, compare);
  // 集合合并 and 判断
  for (int i = 1; i <= m; i++) {
    auto [p, x, y] = a[i];
    bool is_conn = dsu.is_connected(x, y);
    if (p == 1) { // p(x==y)
      dsu.unionXY(x, y);
    } else if (is_conn) { // p(x!=y))
      printf("NO\n");
      return;
    }
  }
  printf("YES\n");
}

// 解题思路: 并查集 + 离散化
// 优化技巧: 优先处理相当的判定
void solve() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    solveOnce();
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}