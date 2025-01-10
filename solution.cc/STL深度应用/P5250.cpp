// == Code Location ==
#include <cstdio>
#include <set>

template <typename T> using Set = std::set<T>;

bool contains(Set<int> &set, int x) { return set.find(x) != set.end(); }

int abs(int a) { return a > 0 ? 0 + a : 0 - a; }

void insert(Set<int> &set, int x) {
  if (!contains(set, x)) {
    set.insert(x);
  } else {
    printf("Already Exist\n");
  }
}

void remove(Set<int> &set, int x) {
  if (set.empty()) {
    printf("Empty\n");
  } else if (contains(set, x)) {
    printf("%d\n", x);
    set.erase(set.find(x)); // 删除元素
  } else {                  // 找最近的元素
    Set<int>::iterator pk, p0, p1;
    // 最近的大于x的元素的位置(没有就往前找最近的)
    p1 = set.upper_bound(x);
    if (p1 == set.end()) {
      p1--;
    }

    // 最近的小于等于xp1的元素的位置 [xp0 <= xp1]
    pk = p0 = p1; // now copy
    if (p0 != set.begin()) {
      p0--;
    }
    if (abs(x - *p0) <= abs(x - *p1)) {
      pk = p0;
    }

    // output answer
    printf("%d\n", *pk);
    set.erase(pk);
  }
}

// 1、STL中自带的set，可以自动去重。
// 2、STL中自带的set，自带排序功能，
// std::lower_bound找出大于等于目标值的位置。
// std::upper_bound是找出大于目标值的位置。
// 3、lower_bound与upper_bound返回的是迭代器，本质上是一个指针：set::iterator
// 4、迭代器为了删除等操作，需要复制出来一份，才能操作。
// 5、指针可以向前向后移动(p++, p--)，但需要特判边界。
// 6、*i,*j代表指针位置的值。
// 7、find返回的也是地址，找不到的话，返回set.end()
void solve(void) {
  int n;
  scanf("%d", &n);

  int op, x;
  Set<int> set;
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &op, &x);
    if (op == 1) {
      insert(set, x);
    }
    if (op == 2) {
      remove(set, x);
    }
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}