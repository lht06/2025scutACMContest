#ifdef LOCAL
#include "dependencies.h"
#else
#include <bits/stdc++.h>
#endif

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

#define fst first
#define snd second
#define range(x) std::begin(x), std::end(x)

using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using pii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vl = std::vector<i64>;
using vp = std::vector<pii>;
using vs = std::vector<std::string>;
using vb = std::basic_string<bool>;
template <typename T> using Heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <typename T> bool chkmin(T& lhs, const T& rhs) { return lhs > rhs ? lhs = rhs, true : false; }
template <typename T> bool chkmax(T& lhs, const T& rhs) { return lhs < rhs ? lhs = rhs, true : false; }
template <typename T> T lowbit(T x) { return x & -x; }

template <unsigned int P> struct Fp {
  unsigned int v = 0;

  // reflection
  template <typename T = int> static constexpr T mod() { return P; }
  template <typename T = int> constexpr T val() { return v; }

  // constructor
  constexpr Fp() = default;
  template <typename T> constexpr Fp(T x) : v(x % mod()) {
    if constexpr (std::is_signed_v<T>) {
      if (v >> 31) {
        v += P;
      }
    }
  }

  // io
  friend std::istream& operator>>(std::istream& is, Fp& rhs) {
    long long v;
    is >> v;
    rhs = v;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, Fp rhs) { return os << rhs.v; }

  // comparision
  friend constexpr bool operator==(Fp lhs, Fp rhs) { return lhs.v == rhs.v; }
  friend constexpr bool operator!=(Fp lhs, Fp rhs) { return lhs.v != rhs.v; }

  // arithmetic
  constexpr Fp& operator+=(Fp rhs) {
    v += rhs.v;
    if (v >= P) v -= P;
    return *this;
  }
  constexpr Fp& operator-=(Fp rhs) {
    v -= rhs.v;
    if (v >> 31) v += P;
    return *this;
  }
  constexpr Fp& operator*=(Fp rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }
  constexpr Fp& operator/=(Fp rhs) {
    v = fpow(rhs.v, P - 2, v);
    return *this;
  }
  template <typename T> constexpr Fp& operator^=(T rhs) {
    v = fpow(v, rhs);
    return *this;
  }
  friend constexpr Fp operator+(Fp lhs, Fp rhs) { return lhs += rhs; }
  friend constexpr Fp operator-(Fp lhs, Fp rhs) { return lhs -= rhs; }
  friend constexpr Fp operator*(Fp lhs, Fp rhs) { return lhs *= rhs; }
  friend constexpr Fp operator/(Fp lhs, Fp rhs) { return lhs /= rhs; }
  template <typename T> friend constexpr Fp operator^(Fp lhs, T rhs) { return lhs ^= rhs; }
  constexpr Fp operator+() const { return *this; }
  constexpr Fp operator-() const { return Fp{} - *this; }
  constexpr Fp operator~() const { return fpow(v, P - 2); }
  template <typename T> constexpr Fp pow(T exp) const { return fpow(v, exp); }

  // x^y * z
  template <typename T> static constexpr unsigned int fpow(unsigned long long x, T y, unsigned long long z = 1) {
    unsigned int n = y % (mod() - 1);
    if constexpr (std::is_signed_v<T>) {
      if (n >> 31) {
        n += P - 1;
      }
    }
    for (; n; n /= 2) {
      if (n & 1) z = z * x % P;
      x = x * x % P;
    }
    return z;
  }
};

using Z353 = Fp<998244353>;
using Z007 = Fp<1000000007>;
using Z009 = Fp<1000000009>;

template <typename Z> struct Combination {
  static inline std::vector<Z> inv{0, 1}, fac{1, 1}, fiv{1, 1};
  static inline int N = 2;
  static void fix(int n) {
    if (N >= n) return;
    inv.resize(n);
    fac.resize(n);
    fiv.resize(n);
    for (int i = N; i < n; ++i) {
      inv[i] = inv[Z::mod() % i] * (Z::mod() - Z::mod() / i);
      fac[i] = fac[i - 1] * i;
      fiv[i] = fiv[i - 1] * inv[i];
    }
    N = n;
  }
  static Z inverse(int n) {
    fix(n + 1);
    return inv[n];
  }
  static Z factorial(int n) {
    fix(n + 1);
    return fac[n];
  }
  static Z facinv(int n) {
    fix(n + 1);
    return fiv[n];
  }
  static Z C(int n, int m) {
    fix(n + 1);
    return fac[n] * fiv[m] * fiv[n - m];
  }
};

template <typename T> struct Fenwick {
  std::vector<T> a;
  int n = 0;
  Fenwick() = default;
  Fenwick(int n, T x = T()) : a(n, x), n(n) {}
  Fenwick(std::vector<T> src) : a(std::move(src)) {
    n = a.size();
    for (int i = 0; i < n; ++i)
      if ((i | (i + 1)) < n) a[i | (i + 1)] += a[i];
  }
  void update(int p, T x) {
    for (int i = p; i < n; i |= i + 1) a[i] += x;
  }
  T sum_pre(int p) const {
    T x = T();
    for (int i = p; ~i; i = (i & (i + 1)) - 1) x += a[i];
    return x;
  }
  T sum(int l, int r) const { return sum_pre(r) - sum_pre(l - 1); }
};

template <typename T> struct FenwickV2 {
  std::vector<T> a, b;
  int n = 0;
  FenwickV2() = default;
  FenwickV2(int n) : a(n), b(n), n(n) {}
  FenwickV2(std::vector<T> src) : a(std::move(src)) {
    b.resize(n = a.size());
    for (int i = n - 1; i > 0; --i) a[i] -= a[i - 1];
    for (int i = 0; i < n; ++i) b[i] = a[i] * i;
    for (int i = 0; i < n; ++i) {
      if ((i | (i + 1)) < n) {
        a[i | (i + 1)] += a[i];
        b[i | (i + 1)] += b[i];
      }
    }
  }
  void add_suf(int p, T x) {
    T y = x * p;
    for (int i = p; i < n; i |= i + 1) {
      a[i] += x;
      b[i] += y;
    }
  }
  void add(int l, int r, T x) {
    add_suf(l, x);
    add_suf(r + 1, -x);
  }
  T sum_pre(int p) {
    T x = T();
    for (int i = p++; ~i; i = (i & (i + 1)) - 1) x += a[i] * p - b[i];
    return x;
  }
  T sum(int l, int r) { return sum_pre(r) - sum_pre(l - 1); }
};

void init1();
void init2();
void solution(int cas);

int main() {
  init1();
  int T = 1;
  std::cin >> T;
  init2();
  for (int cas = 1; cas <= T; ++cas) {
    solution(cas);
  }
}

using Array = std::array<uint8_t, 256>;
using Matrix = std::array<uint8_t, 16>;

constexpr uint8_t gmul(uint8_t a, uint8_t b) {
  uint8_t c = 0;
  for (int i = 0; i < 8; ++i) {
    if (b >> i & 1) c ^= a;
    a = a << 1 ^ (a >> 7 & 1 ? 0x1b : 0);
  }
  return c;
}

Matrix inverse(const Matrix& a) {
  Array inv{};
  for (int i = 1; i < 256; ++i) {
    for (int j = 1; j < 256; ++j) {
      if (gmul(i, j) == 1) {
        inv[i] = j;
      }
    }
  }

  std::array<std::array<uint8_t, 8>, 4> c{};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      c[i][j] = a[i + j * 4];
    }
    c[i][i + 4] = 1;
  }

  for (int i = 0; i < 4; ++i) {
    if (c[i][i] == 0) {
      for (int j = i + 1; j < 4; ++j) {
        if (c[j][i] != 0) {
          std::swap(c[i], c[j]);
          break;
        }
      }
    }
    uint8_t x = inv[c[i][i]];
    for (int j = 0; j < 8; ++j) c[i][j] = gmul(c[i][j], x);
    for (int j = 0; j < 4; ++j) {
      if (i == j) continue;
      x = c[j][i];
      for (int k = 0; k < 8; ++k) c[j][k] ^= gmul(c[i][k], x);
    }
  }

  Matrix b{};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      b[i + j * 4] = c[i][j + 4];
    }
  }
  return b;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
  Matrix c{};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) {
        c[i + j * 4] ^= gmul(a[i + k * 4], b[k + j * 4]);
      }
    }
  }
  return c;
}

uint8_t read_byte() {
  std::string s;
  std::cin >> s;
  return std::stoi(s, nullptr, 16);
}

void init1() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
}

std::array<int, 16> rot{0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11}, tor;
Array perm, mrep;
const Matrix P{2, 1, 1, 3, 3, 2, 1, 1, 1, 3, 2, 1, 1, 1, 3, 2}, Q = inverse(P);

void init2() {
  for (int i = 0; i < 16; ++i) tor[rot[i]] = i;
  for (int i = 0; i < 256; ++i) perm[i] = read_byte();
  for (int i = 0; i < 256; ++i) mrep[perm[i]] = i;
}

struct Treap {
  Treap *lson, *rson;
  int size;
  int key;
  i64 sum;

  struct null_tag {};
  Treap(null_tag) : lson(this), rson(this), size(0), key(0), sum(0) {}
  Treap(int key) : lson(null_node()), rson(null_node()), size(1), key(key), sum(key) {}
  static Treap* null_node() {
    static Treap node{null_tag{}};
    return &node;
  }

  void pull() {
    size = lson->size + rson->size + 1;
    sum = lson->sum + rson->sum + key;
  }

  template <typename Pred> static std::pair<Treap*, Treap*> split(Treap* root, const Pred& pred) {
    std::pair res{root, root};
    if (root != null_node()) {
      if (pred(*root)) {
        std::tie(res.fst, root->lson) = split(root->lson, pred);
      } else {
        std::tie(root->rson, res.snd) = split(root->rson, pred);
      }
      root->pull();
    }
    return res;
  }

  static Treap* merge(Treap* left, Treap* right) {
    static std::mt19937 rng{114514};
    if (left == null_node()) return right;
    if (right == null_node()) return left;
    Treap* res;
    if ((int)(rng() / 2) % (left->size + right->size) < left->size) {
      res = left;
      left->rson = merge(left->rson, right);
    } else {
      res = right;
      right->lson = merge(left, right->lson);
    }
    res->pull();
    return res;
  }

  static auto comp_fn(int x) {
    return [x](const Treap& node) { return x < node.key; };
  }

  static void insert(Treap*& root, int key) {
    auto [left, right] = split(root, comp_fn(key));
    root = merge(merge(left, new Treap(key)), right);
  }

  static int erase(Treap*& root, int key, int num = 1) {
    Treap *left, *middle, *right;
    std::tie(root, right) = split(root, comp_fn(key));
    std::tie(left, root) = split(root, comp_fn(key - 1));
    std::tie(root, middle) = split(root, [&num](const Treap& node) {
      if (node.lson->size < num) {
        num -= node.lson->size + 1;
        return false;
      }
      return true;
    });
    num = root->size;
    root = merge(merge(left, middle), right);
    return num;
  }
};

template <typename T> struct Manacher {
  std::vector<T> t;
  std::vector<int> a;
  Manacher(const T* s, int n, T mid = '#', T tail = '$') : t(n * 2 + 2), a(n * 2 + 2) {  // s[0] ... s[n-1]
    int m = 0;
    t[m++] = mid;
    for (int i = 0; i < n; i++) t[m++] = s[i], t[m++] = mid;
    t[m] = tail;
    a[0] = 1;
    for (int i = 1, j = 0, r = 1; i < m; i++) {
      a[i] = i < r ? std::min(r - i, a[j * 2 - i]) : 1;
      while (t[i + a[i]] == t[i - a[i]]) a[i] += 1;
      if (chkmax(r, i + a[i])) j = i;
    }
  }
  bool check(int l, int r) const { return a[l + r + 1] > r - l + 1; }  // [l, r]
};


void solution([[maybe_unused]] int cas) {
  Matrix input, output, key, buf;
  for (int i = 0; i < 16; ++i) {
    input[i] = read_byte();
  }
  for (int i = 0; i < 16; ++i) {
    output[i] = read_byte();
  }

  output = Q * output;
  for (int i = 0; i < 16; ++i) buf[i] = output[tor[i]];
  output.swap(buf);
  for (int i = 0; i < 16; ++i) output[i] = mrep[output[i]];
  for (int i = 0; i < 16; ++i) key[i] = input[i] ^ output[i];

  for (int i = 0; i < 16; ++i) {
    std::cout << "0x" << std::hex << (int)key[i] << " \n"[i == 15];
  }
}