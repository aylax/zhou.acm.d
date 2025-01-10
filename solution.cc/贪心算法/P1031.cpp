// == Code Location ==
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

void solve(void) {
  int n;
  scanf("%d", &n);

  int sum = 0;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }

  int k = 0; // 移动次数
  int avg = sum / n;
  for (int i = 0; i < n - 1; i++) {
    if (a[i] != avg) { // 数量和<均值>不一致, 就把<差值>移到下一堆
      a[i + 1] += (a[i] - avg); // <差值>存到下一堆纸牌中
      a[i] = avg;               // 当前牌堆达成均分
      k += 1;                   // 操作次数加1
    }
  }

  printf("%d\n", k);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}