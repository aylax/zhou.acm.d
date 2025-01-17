// == Code Location ==
#include <cstdio>

bool ispal(int n) {
  int k = n, s = 0;
  while (k > 0) {
    s = s * 10 + k % 10;
    k = k / 10;
  }
  return s == n;
}

bool isprime(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

void solve(void) {
  int a, b;
  scanf("%d %d", &a, &b);

  for (int i = a; i <= b; i++) {
    // 优先判断回文数
    if (ispal(i) && isprime(i)) {
      printf("%d\n", i);
    }
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}
