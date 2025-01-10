// == Code Location ==
#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int max(int a[], int l, int r) {
  int k = a[l];
  for (int i = l; i <= r; i++) {
    k = max(k, a[i]);
  }
  return k;
}

void assign(int xs[], int l, int r, int x) {
  for (int i = l; i <= r; i++) {
    xs[i] = x;
  }
}

bool some(int a, int b) { return (a & b) != 0; }

// 状态压缩处理(二进制)
// F[i][j] = v: 截至到第i个元素, 该元素在二进制下第j位的数字为1的情况下
// 满足条件的最长序列的长度v
// 解释:
// 前提: Bin(A[i-1])[j] == 1 成立
// 如果: Bin(A[i])[j] == 1 也成立
// 那么: Ai & Ai-1 != 0, 构成序列, (构成通路, 其他列能访问该列)
// 否则: 不构成序列
// 如果构成通路((Bin(A[i-1])[j] & Bin(A[i])[j]) != 0)
// 则 V = Max(P[j=0..len]); 否则 V = F[i-1][j]
void solve1(void) {
  int n; // 数量
  scanf("%d", &n);

  int a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  int len = 32; // binary length
  int f[n + 1][len + 1] = {};

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < len; j++) {
      f[i][j] = f[i - 1][j]; // 首先继承值
      if (some(a[i], 1 << j)) {
        f[i][j] += 1;
      }
    }

    f[i][len] = max(f[i], 0, len - 1); // f[i][len]中存最值
    // 如果构成通路((Bin(A[i-1])[j] & Bin(A[i])[j]) != 0)
    // 则 V = Max(P[j=0..len]); 否则 V = F[i-1][j]
    for (int j = 0; j < len; j++) {
      if (some(a[i], 1 << j)) { // check
        f[i][j] = f[i][len];
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, f[i][len]);
  }
  printf("%d\n", ans);
}

// 线性动态规划 复杂度 O(n^2)
void solve0(void) {
  int n; // 数量
  scanf("%d", &n);

  int a[n + 1] = {};
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  int f[n + 1] = {};
  assign(f, 1, n, 1);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (some(a[j], a[i])) { // check
        f[i] = max(f[j] + 1, f[i]);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    f[0] = max(f[i], f[0]);
  }
  printf("%d\n", f[0]);
}

int main() {
  freopen("data.in", "r", stdin);
  solve1();
  fclose(stdin);
  return 0;
}