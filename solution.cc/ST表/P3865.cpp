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

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  vec<int> l(m), r(m);
  for (int j = 0; j < m; j++) {
    scanf("%d %d", &l[j], &r[j]);
  }
  prelogn(n);
  auto stmax = SparseTable<int>(a, std::max<int>);
  for (int j = 0; j < m; j++) {
    printf("%d\n", stmax.query(l[j], r[j]));
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}