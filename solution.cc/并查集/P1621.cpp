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

// 欧拉素数筛: 找出 [0, n]范围内的素数
vec<int> PrimeSieveOfEuler(int n) {
  vec<bool> isprime(n + 1, true);
  isprime[0] = isprime[1] = false;
  vec<int> prime;
  for (int i = 2; i <= n; i++) {
    if (isprime[i]) {
      prime.push_back(i);
    }
    for (auto p : prime) {
      if (p * i > n) {
        break;
      }
      isprime[i * p] = false; // 去除素数的倍数
      // 每次只筛小于i的, 防止重复筛选数字
      if (i % p == 0) {
        break;
      }
    }
  }
  return prime;
}

// 解题思路:
// 先通过欧拉筛数法, 筛出所有的素数
// 然后, 对大于等于k的所有素数做如下操作:
// 找出素数p在集合(A,B)内的所有倍数,
// 将这些倍数归并到同一集合中
void solve(void) {
  int m, n, k;
  scanf("%d %d %d", &m, &n, &k);

  // 预处理, 筛出n以内的所有素数
  vec<int> prime = PrimeSieveOfEuler(n);

  // 并查集
  quickunion::DSU dsu = quickunion::DSU(n + 1);

  // 找到大于k的素数
  auto it = std::lower_bound(prime.begin(), prime.end(), k);

  // 找出素数p在集合(A,B)内的所有倍数,
  // 将这些倍数归并到同一集合中
  for (; it != prime.end(); it++) {
    int p = (*it);
    // 找出 比m大的, 最小的p的倍数t
    int t = ((m - 1) / p + 1) * p;
    for (int j = t + p; j <= n; j += p) {
      dsu.unionXY(t, j);
    }
  }

  // 输出结果
  int ret = 0;
  for (int i = m; i <= n; i++) {
    if (dsu.find(i) == i) {
      ret += 1;
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