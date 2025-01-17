// == Code Location ==
#include <cmath>
#include <cstdio>
#include <vector>

template <typename T> using vec = std::vector<T>;

struct data {
  int w;
  int l;
};

// 判断本轮比赛是否结束
bool check(int w, int l, int p) {
  return (std::max(w, l) >= p) and (std::abs(w - l) >= 2);
}

void print(vec<data> &a) {
  for (auto &[w, l] : a) {
    printf("%d:%d\n", w, l);
  }
}

void solve() {
  char c;
  vec<data> A11, A21;
  int W11(0), L11(0), W21(0), L21(0);

  while (scanf("%c", &c) != EOF) { // EOF end of file
    if (c == 'E') {
      break;
    } else if (c == 'W') {
      W11 += 1;
      W21 += 1;
    } else if (c == 'L') {
      L11 += 1;
      L21 += 1;
    } else {
      // do nothing
    }

    if (check(W11, L11, 11)) {
      A11.push_back({W11, L11});
      W11 = L11 = 0;
    }
    if (check(W21, L21, 21)) {
      A21.push_back({W21, L21});
      W21 = L21 = 0;
    }
  }
  // 剩余局数
  A11.push_back({W11, L11});
  A21.push_back({W21, L21});

  print(A11);
  printf("\n");
  print(A21);
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}