// == Code Location ==
#include <cstdio>

const int len = 2e5 + 10;

int q[len], head = 0, tail = 1;

// 单调非递增队列: 将数值L入队, 然后返回队首元素
int deqmax(int f[], int l, int r) {
  while (head <= tail and r < q[head]) {
    head += 1;
  }
  while (head <= tail and f[l] >= f[q[tail]]) {
    tail -= 1;
  }
  tail += 1, q[tail] = l;
  return q[head];
}

// 线性动态规划
// 单调队列维护区间最值
// 动态规划缓存计算结果
void solve(void) {
  int n, l, r; // 个数N, 区间[l,R]
  scanf("%d %d %d", &n, &l, &r);

  int a[n + 1] = {};
  for (int i = 0; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  int f[n + 1 + r] = {};

  for (int i = n; i >= 0; i--) {
    int j = deqmax(f, i + l, i + r);
    f[i] = f[j] + a[i];
  }
  printf("%d\n", f[0]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}