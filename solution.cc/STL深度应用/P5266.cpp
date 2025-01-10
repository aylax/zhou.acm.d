// == Code Location ==
#include <cstdio>
#include <map>
#include <string>

using str = std::string;

template <typename K, typename V> using Hash = std::map<K, V>;

bool contains(Hash<str, int> &h, str x) { return h.find(x) != h.end(); }

void query(Hash<str, int> &h, str name) {
  if (contains(h, name)) {
    printf("%d\n", h[name]);
  } else {
    printf("Not found\n");
  }
}

void insert(Hash<str, int> &h, str name, int score) {
  h[name] = score;
  printf("OK\n");
}

void remove(Hash<str, int> &h, str name) {
  if (contains(h, name)) {
    h.erase(name);
    printf("Deleted successfully\n");
  } else {
    printf("Not found\n");
  }
}

void count(Hash<str, int> &h) { printf("%d\n", h.size()); }

void solve(void) {
  int n;
  scanf("%d", &n);

  char buff[50]; // 最长英文单词的长度?

  int op, score;
  Hash<str, int> h;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%s %d", &buff, &score);
      insert(h, buff, score);
    } else if (op == 2) {
      scanf("%s", &buff);
      query(h, buff);
    } else if (op == 3) {
      scanf("%s", &buff);
      remove(h, buff);
    } else if (op == 4) {
      count(h);
    } else {
    }
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}