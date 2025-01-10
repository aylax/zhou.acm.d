// == Code Location ==
#include <cstdio>
#include <vector>

using i64 = long long;
template <typename T> using vec = std::vector<T>;

bool check(vec<int> &a, int h, i64 sum) {
  i64 s = 0;
  int n = a.size();
  for (int i = 0; i < n; i++) {
    if (a[i] > h) {
      s += 1LL * (a[i] - h);
      if (s >= sum) {
        return true;
      }
    }
  }
  return false;
}

void solve(void) {
  int n;
  i64 sum;
  scanf("%d %lld", &n, &sum);

  int maxh = -1; // 最大高度

  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (maxh < a[i]) {
      maxh = a[i];
    }
  }

  int l = 0, r = maxh;
  while (l < r) {
    int mid = (l + r + 1) / 2; // +1 是为了保证每次 mid > l
    if (check(a, mid, sum)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }

  printf("%d\n", l);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}