// == Code Location ==
#include <cstdio>
#include <unordered_map>

template <typename K, typename V> using Hash = std::unordered_map<K, V>;

bool contains(Hash<int, int> &hash, int x) {
  return hash.find(x) != hash.end();
}

void solve(void) {
  int n;
  scanf("%d", &n);

  int c;
  scanf("%d", &c);

  int k;
  Hash<int, int> hash;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &k);
    hash[k] += 1;
  }

  int ret = 0;
  for (auto [k, num] : hash) {
    if (contains(hash, k - c)) {
      ret += 1LL * hash[k - c] * hash[k]; // if contains
    }
  }
  printf("%d\n", ret);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}