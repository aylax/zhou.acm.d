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

  int k;
  Hash<int, int> hash;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &k);
    hash[k] = i;
  }

  int m;
  scanf("%d", &m);

  int q;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &q);
    printf("%d\n", hash[q]);
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}