// == Code Location ==
#include <cstdio>

struct task {
  int d; // 租借教室数量
  int s; // 租借开始日期
  int t; // 租借结束日期
};

// 检查是否能处理完Task[1..mid]之间的所有任务
bool check(task q[], int a[], int n, int mid) {
  int d[n + 1] = {}; // 差分数组

  // 租借开始时间, 租借结束时间, 租借天数
  int v, l, r;

  // 通过差分数组, 预处理任务计划
  for (int j = 1; j <= mid; j++) {
    v = q[j].d;
    l = q[j].s, r = q[j].t;
    d[l] += v, d[r + 1] -= v;
  }

  int total = 0; // 当日租借总数量
  for (int i = 1; i <= n; i++) {
    total += d[i]; // 累加租借数量
    if (total > a[i]) {
      return false;
    }
  }
  return true;
}

// 如果 Task[mid]可以完成,
// 说明 Task[1..mid-1]都能完成
// 此时 Task区间就设为[mid..r]
// 否则 Task区间设为[l..mid]
int find(task q[], int a[], int n, int m) {
  int l = 1, r = m;
  while (l < r) {
    int mid = (l + r) / 2;
    if (check(q, a, n, mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

// 差分数组+二分查找
void solve(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  int a[n + 1] = {}; // 可用数量
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  task q[m + 1] = {}; // 任务数量
  for (int j = 1; j <= m; j++) {
    scanf("%d %d %d", &q[j].d, &q[j].s, &q[j].t);
  }

  // 如果都能满足, 直接输出
  if (check(q, a, n, m)) {
    printf("%d\n", 0);
  } else {
    int k = find(q, a, n, m);
    printf("%d\n%d\n", -1, k);
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}