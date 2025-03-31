#include <bits/stdc++.h>

using i64 = long long;

namespace __random {
    // __random integer number
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
};

// [l, r)
template <class T>
T randInt(T l, T r) {
    assert(l < r);
    return __random::rng() % (r - l) + l;
}

using Point = std::pair<int, int>;

constexpr int Limit = 1E9;

Point randPoint() {
    int x = randInt(0, Limit + 1);
    int y = randInt(0, Limit + 1);
    return Point(x, y);
}

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    // 外 内

    std::vector<Point> ps;
    
    ps.emplace_back(0, 0);
    ps.emplace_back(0, Limit);
    ps.emplace_back(Limit, 0);

    #define x first
    #define y second

    Point cur = Point(0, Limit);
    for (int i = 3; i < n; i++) {
        cur.y -= 1;
        cur.x += 100 + n - i;
        ps.push_back(cur);
    }

    for (int i = 0; i < m; i++) {
        Point p = randPoint();
        while (p.x + p.y >= Limit or p.x == 0 or p.y == 0) {
            p = randPoint();
        }

        ps.push_back(p);
    }

    for (auto [x, y] : ps) {
        std::cout << x << ' ' << y << '\n';
    }


    return 0;
}