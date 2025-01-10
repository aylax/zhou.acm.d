// == Code Location ==
#include <cstdio>
#include <limits>
#include <unordered_map>

using i64 = long long;

using Hash = std::unordered_map<int, int>;

const int INT_MAX = std::numeric_limits<int>::max();
const int mod = 998244353; // mod

// 任何一个大于1的自然数 N,如果N不为质数，
// 那么N可以唯一分解成有限个质数的乘积
// N = p1^e1 x p2^e2 x... xpn^ek,
// 此处p1<p2<...<pn, 且均为质数，其中指数ei是正整数。
// 这样的分解称为 N 的标准分解式。(素因数分解)
void primefact(Hash &dec, int n) {
  for (int p = 2; p <= n / p; p++) {
    while (n % p == 0) { // 统计个数 E1
      n /= p, dec[p] += 1;
    }
  }
  // 剩余部分,本身也是质数
  if (n > 1) {
    dec[n] += 1;
  }
}

// 求解N的因子个数
// 前提: N已通过标准分解式, 将结果存储到Hash中
i64 factnum(Hash &dec) {
  i64 ret = 1;
  for (auto [_, e] : dec) {
    ret = (ret * (e + 1)) % mod;
  }
  return ret;
}

// 找到hp数组中, p的指数个数最少元素的索引
int indexOfLeast(Hash hp[], int p, int n) {
  int minIndex = -1;
  int minValue = INT_MAX;
  for (int i = 1; i <= n; i++) {
    if (minValue > hp[i][p]) {
      minValue = hp[i][p];
      minIndex = i;
    }
  }
  return minIndex;
}

// 解题思路:
// 本题中, 每个星球的开发潜力值, 都可以表示为资源值(N)的因数个数(C)
// 通过素因数分解法, 将对N的因数个数C的问题求解, 转换成标准分解式下的指数形式
// N = p1^e1 x p2^e2 x... xpn^ek, C = (e1+1) x (e2+1) x ... (ek+1)
// 将其简化为: C = (e1, e2, ...ek)
// 而问题要求的所有资源值的乘积 CC = C1 * C2 * C3, 也用上述的指数形式表示
// 并将 W 也分解为该形式, C(W) = (e1, e2, ...)
// 此时问题转化为 要使资源 RES 最大 ,
// 需要将 W中的(e1,..ek) 分别添加到在那几个素数的指数上
// 观察到, 由于是乘法运算, 增大较小值更佳
// 证明: 如果 a < b, 可得 (a + 1) x b > (b + 1) x a
void solve(void) {
  int n, w;
  scanf("%d %d", &n, &w);

  Hash allocator;
  // 对W进行素因数分解, 并将结果存储到allocator中
  primefact(allocator, w);

  int a[n + 1];
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  Hash hp[n + 1];
  // 存储a[n+1]的素因数分解结果
  for (int i = 1; i <= n; i++) {
    primefact(hp[i], a[i]);
  }

  for (auto [p, _] : allocator) { // 遍历W的素因数
    // 如果p中还有可分配的量, 就将其分配到含p量最少的元素中
    while (allocator[p] > 0) {
      int index = indexOfLeast(hp, p, n);
      hp[index][p] += 1;
      allocator[p] -= 1;
    }
  }

  i64 ret = 1;
  for (int i = 1; i <= n; i++) {
    ret = (ret * factnum(hp[i])) % mod;
  }
  printf("%lld", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}