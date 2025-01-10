// == Code Location ==
#include <cstdio>
#include <unordered_set>

template <typename T> using Set = std::unordered_set<T>;

bool contains(Set<int> &set, int x) { return set.find(x) != set.end(); }

void solve(void) {
  int m;
  scanf("%d", &m);
  for (int k = 1; k <= m; k++) {
    int n, x;
    scanf("%d", &n);

    Set<int> set;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &x);
      if (!contains(set, x)) {
        set.insert(x);
        printf("%d ", x);
      }
    }
    printf("\n");
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}