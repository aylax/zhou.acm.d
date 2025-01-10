// == Code Location ==
#include <cstdio>
#include <string>
#include <unordered_set>

using str = std::string;

template <typename T> using Set = std::unordered_set<T>;

bool contains(Set<str> &set, str x) { return set.find(x) != set.end(); }

void solve(void) {
  int n, c;
  scanf("%d", &n);

  char buff[50]; // 最长英文单词的长度?
  Set<str> sets[n + 1];
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c);
    for (int j = 1; j <= c; j++) {
      scanf("%s", &buff);
      if (!contains(sets[i], buff)) {
        sets[i].insert(buff);
      }
    }
  }

  int m;
  scanf("%d", &m);
  for (int k = 1; k <= m; k++) {
    scanf("%s", &buff);
    for (int i = 1; i <= n; i++) {
      if (contains(sets[i], buff)) { // 判断元素是否存在
        printf("%d ", i);
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