// == Code Location ==
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

int find(vec<int> &a, int x) {
  int l = 0, r = a.size() - 1;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (x == a[mid]) {
      return mid;
    }

    if (x > a[mid]) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return -1;
}

void solve(void) {
  int n;
  scanf("%d", &n);

  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  int k, s;
  scanf("%d %d", &k, &s);
  if (not(find(a, s - k) < 0)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}