// == Code Location ==
#include <cstdio>
#include <functional>
#include <vector>

template <typename T> // template for vector
using vec = std::vector<T>;

vec<int> logn;
void prelogn(int n) { // prepare handle log2
  logn.assign(n + 1, 0);
  logn[1] = 0, logn[2] = 1;
  for (int i = 3; i <= n; i++) {
    logn[i] = logn[i / 2] + 1;
  }
}

template <typename T> // template for sparse table
struct SparseTable {
private:
  using fn = std::function<T(const T &, const T &)>;

  vec<vec<T>> st;
  fn merge;

public:
  SparseTable(const vec<T> &a, fn func) {
    int n = a.size();
    int m = logn[n];
    st.assign(n + 1, vec<int>(m, 0));

    for (int i = 1; i <= n; i++) {
      st[i][0] = a[i - 1];
    }

    merge = func;
    for (int j = 1; j <= m; j++) {
      int s = 1 << (j - 1);
      for (int i = 1; i + (s << 1 - 1) <= n; i++) {
        st[i][j] = merge(st[i][j - 1], st[i + s][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    int s = logn[r - l + 1];
    return merge(st[l][s], st[r - (1 << s) + 1][s]);
  }
};

// 问题分析:
// 得分 c = ax * by
// 1. 小L先选, 小Q后选
// 2. 小L希望得分尽可能大, 小Q希望得分尽可能小
// 分类讨论: 双方都采取最优策略
// 小Q的视角:
// 如果 L.ax >= 0, 则 Q.by = Min(B[1..m])
// 如果 L.ax <  0, 则 Q.by = Max(B[1..m])

// 小L的视角1: 预判小Q会采取的最优策略
// 选择 L.ax >= 0, 则 Q.by = Min(B[1..m])
// 如果 Q.by >= 0, 则 L.ax = 最大的非负数
// 如果 Q.by <  0, 则 L.ax = 最小的非负数
// 小L的视角2: 预判小Q会采取的最优策略
// 选择 L.ax <  0, 则 Q.by = Max(B[1..m])
// 如果 Q.by >= 0, 则 L.ax = 最大的负数
// 如果 Q.by <  0, 则 L.ax = 最小的负数

// 共计要维护6组ST表
// A: 区间最大值, 区间最小值
// A: 负数区间最大值, 非负区间最小值
// B: 区间最大值, 区间最小值
#include <climits>
using i64 = long long;
void solve(void) {
  int n, m, q;
  scanf("%d %d %d", &n, &m, &q);

  vec<int> aint(n); // 整数
  vec<int> aneg(n); // 负数
  vec<int> anon(n); // 非负
  for (int i = 0; i < n; i++) {
    scanf("%d", &aint[i]);
    if (aint[i] >= 0) {
      aneg[i] = INT_MIN;
      anon[i] = aint[i];
    } else {
      aneg[i] = aint[i];
      anon[i] = INT_MAX;
    }
  }
  vec<int> bint(m); // 整数
  for (int i = 0; i < m; i++) {
    scanf("%d", &bint[i]);
  }

  // 预处理Log2_N
  prelogn(std::max<int>(n, m));

  // A  6张ST表
  // A: 区间最大值, 区间最小值
  // A: 负数区间最大值, 非负区间最小值
  auto stmaxAint = SparseTable<int>(aint, std::max<int>);
  auto stminAint = SparseTable<int>(aint, std::min<int>);
  auto stmaxAneg = SparseTable<int>(aneg, std::max<int>);
  auto stminAnon = SparseTable<int>(anon, std::min<int>);

  // B  2张ST表
  // B: 区间最大值, 区间最小值
  auto stmaxBint = SparseTable<int>(bint, std::max<int>);
  auto stminBint = SparseTable<int>(bint, std::min<int>);

  int L1, R1, L2, R2;
  int Xmax, Xmin;
  int XnegMax, XnonMin;
  int Ymax, Ymin;
  for (int i = 0; i < q; i++) {
    scanf("%d %d", &L1, &R1);
    scanf("%d %d", &L2, &R2);
    // X: 4个最值
    Xmax = stmaxAint.query(L1, R1);
    Xmin = stminAint.query(L1, R1);
    XnegMax = stmaxAneg.query(L1, R1);
    XnonMin = stminAnon.query(L1, R1);
    // Y: 2个最值
    Ymax = stmaxBint.query(L2, R2);
    Ymin = stminBint.query(L2, R2);

    // 最优解求解函数
    auto best = [Ymax, Ymin](int x) -> i64 {
      return 1ll * x * (x < 0 ? Ymax : Ymin);
    };

    // 分条件讨论
    i64 ans = std::max<i64>(best(Xmax), best(Xmin));
    if (XnegMax != INT_MIN) { ans = std::max<i64>(best(XnegMax), ans); }
    if (XnonMin != INT_MAX) { ans = std::max<i64>(best(XnonMin), ans); }

    printf("%lld\n", ans);
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}