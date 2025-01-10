// == Code Location ==
#include <cstdio>

template <class T> using compare = bool (*)(T, T);

int max(int a, int b) { return a > b ? a : b; }

void assign(int xs[], int l, int r, int x) {
  for (int i = l; i <= r; i++) {
    xs[i] = x;
  }
}

const int len = 1e5 + 5;
int a[len], n; // 数组a, 元素个数n

// 循环读取直到读到 文件流终止符(EOF)
void readin(void) {
  n = 1;
  while (scanf("%d", &a[n]) != EOF) {
    n += 1;
  }
  n = n - 1;
}

// 在s序列中, 找到第一个不满足ord(s[k], x)的元素的位置
int findl(int s[], int l, int r, int x, compare<int> ord) {
  while (l < r) {
    int mid = (l + r) / 2;
    if (ord(s[mid], x)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

// 最长单调(Order[??])子序列的长度
// ?? 需要被指定; 可以为递增、递减等
int longest(compare<int> ord) {
  int s[n + 1] = {0, a[1]};
  int top = 1; // 最长子序列的长度
  for (int i = 2; i <= n; i++) {
    if (ord(s[top], a[i])) { // 将符合ord条件的元素入栈
      top += 1;
      s[top] = a[i];
    } else { // 查找并替换元素
      int k = findl(s, 1, top, a[i], ord);
      s[k] = a[i];
    }
  }
  return top;
}

// 单调栈 + 二分查找(nlogn)
void solve1(void) {
  int len;
  //  计算最长的单调非递增子序列的长度
  len = longest([](int a, int b) { return a >= b; });
  printf("%d\n", len);

  // 计算最长的单调递增子序列的长度
  len = longest([](int a, int b) { return a < b; });
  printf("%d\n", len);
}

// 线性动态规划 时间复杂度 O(n^2)
// Output({A, B})
// A: 求序列中: 最长的单调非递增子序列的长度
// B: 求序列中: 最长的单调递增子序列的长度
// F[i]: 将第A[i]元素,作为序列末尾元素时, 最长的单调非递增序列的长度;
// G[i]: 将第A[i]元素,作为序列末尾元素时, 最长的单调递增序列的长度;
void solve0(void) {
  int f[n + 1];
  assign(f, 0, n, 1);

  int g[n + 1];
  assign(g, 0, n, 1);

  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 1; j--) {
      if (a[j] < a[i]) {
        g[i] = max(g[j] + 1, g[i]);
      } else {
        f[i] = max(f[j] + 1, f[i]);
      }
    }
  }

  // 从所有的子序列中归纳出最大值
  for (int i = 1; i <= n; i++) {
    f[0] = max(f[i], f[0]);
    g[0] = max(g[i], g[0]);
  }

  printf("%d\n%d\n", f[0], g[0]);
}

int main() {
  freopen("data.in", "r", stdin);
  readin();
  solve1();
  fclose(stdin);
  return 0;
}