// == Code Location ==
#include <climits>
#include <cstdio>
#include <vector>

using i64 = long long;
template <typename T> using vec = std::vector<T>;

bool check(vec<int> &a, i64 t, i64 m) {
  i64 k = 0;
  int n = a.size();
  for (int i = 0; i < n; i++) {
    k += (t / a[i]);
    if (k >= m) {
      return true;
    }
  }
  return false;
}

void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  int mint = INT_MAX; // 单个检票口的最少等待时间
  int maxt = INT_MIN; // 单个检票口的最多等待时间

  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (maxt < a[i]) {
      maxt = a[i];
    }
    if (mint > a[i]) {
      mint = a[i];
    }
  }

  i64 l = 1LL * mint;     // M名选手的通过时间下限
  i64 r = 1LL * maxt * m; // M名选手的通过时间上限
  while (l < r) {
    i64 mid = (l + r) / 2;
    if (check(a, mid, m)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  printf("%lld\n", l);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}