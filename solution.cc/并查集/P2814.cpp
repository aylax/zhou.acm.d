// == Code Location ==
#include <cstdio>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using str = std::string;
template <typename K, typename V> using Hash = std::unordered_map<K, V>;
template <typename T> using vec = std::vector<T>;

// 基于数组的快速查询并查集实现
namespace quickfind {
// DisjointSetUnion 并查集 实现1
struct DSU {       // 时间复杂度: 查询 O(1), 修改 O(n)
  vec<int> arr;    // 底层数据, 存储元素所属集合的编号
  DSU(int n) {     // 初始化时, 每个元素本身构成一个集合
    arr.resize(n); // 分配内存空间
    std::iota(arr.begin(), arr.end(), 0); // 递增赋值
  }

  int size() { return arr.size(); }

  // 查找元素x所在的集合编号
  int find(int x) { //
    return arr[x];
  }

  // 判断元素x和元素y是否属于同一集合
  bool is_connected(int x, int y) { return find(x) == find(y); }

  // 将归并两个元素的集合
  void unionXY(int x, int y) {
    int setx = find(x);
    int sety = find(y);
    if (setx == sety) {
      return;
    }
    for (int i = 0; i < arr.size(); i++) {
      if (arr[i] == sety) {
        arr[i] = setx;
      }
    }
  }
};
} // namespace quickfind

// --------------- Hash DB -------------
Hash<str, int> db;  // Hash<name, id>
Hash<int, str> dbk; // Hash<id, name>
int n = 0;          // inc id
int nextid() { return n += 1; }

// get sno of name,
// create it when name not exists,
int findByName(str name) {
  if (db.find(name) == db.end()) {
    int id = nextid();
    db[name] = id;
    dbk[id] = name;
  }
  return db[name];
}

str findById(int id) { return dbk[id]; }
// ------------- Hash DB END -----------

void iprint(char s[]) {
  for (int i = 0; i < 12; i++) {
    printf("%c", s[i]);
  }
}

// Question Solution Here
struct node {
  int x; // id of parent
  int y; // id of child
};

void solve(void) {
  char ch;
  char buff[12];
  node cur;
  vec<node> all;
  vec<str> query;
  str parent, child, query_name;
  // %[^\n] 读取一行(不包含换行符)
  while (scanf("%s", buff) != EOF) {
    ch = buff[0];
    char *name = buff + 1;
    if (ch == '$') {
      break;
    }

    if (ch == '#') {
      parent = name;
      cur.x = findByName(parent);
    } else if (ch == '+') {
      child = name;
      cur.y = findByName(child);
      // printf("[P]%s [S]%s\n", parent.c_str(), child.c_str());
      all.push_back(cur);
    } else {
      query_name = name;
      query.push_back(query_name);
    }
  }

  // 并查集处理亲子关系
  quickfind::DSU dsu = quickfind::DSU(n + 1);
  for (auto [x, y] : all) {
    dsu.unionXY(dsu.find(x), y);
  }

  // 查询
  int x, y;
  str xname;
  for (str yname : query) {
    y = db[yname];
    x = dsu.find(y);
    xname = dbk[x];
    printf("%s ", yname.c_str());
    printf("%s\n", xname.c_str());
  }
}

int main() {
  freopen("data.in", "r", stdin);
  solve();
  fclose(stdin);
  return 0;
}