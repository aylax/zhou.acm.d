// == Code Location ==
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

void setzero(vec<int> &a) {
  for (int i = 1; i < 10; i++) {
    a[i] = 0;
  }
}

bool check(vec<int> &a) {
  for (int i = 1; i < 10; i++) {
    if (a[i] != 1) {
      return false;
    }
  }
  return true;
}

void fillin(vec<int> &a, int n) {
  while (n > 0) {
    a[n % 10] += 1;
    n /= 10;
  }
}

void solve(void) {
  int cnt = 0;
  vec<int> a(10);
  for (int i = 123; i <= 329; i++) {
    int j = i * 2;
    int k = i * 3;
    setzero(a);
    fillin(a, i);
    fillin(a, j);
    fillin(a, k);
    if (check(a)) {
      cnt += 1;
      printf("%d %d %d\n", i, j, k);
    }
  }

  if (not(cnt > 0)) {
    printf("No!!!\n");
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}