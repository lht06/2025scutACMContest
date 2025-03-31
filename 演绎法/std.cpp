#include <bits/stdc++.h>

using i64 = long long;

using Reach = std::bitset<200>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<int>{});
    std::vector<Reach> s(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x -= 1, y -= 1;
        adj[y].push_back(x);
    }

    auto search = [&adj](int st) -> Reach {
        Reach s{};
        s[st] = 1;
        auto dfs = [&](auto &&self, int x) -> void {
            for (int y : adj[x]) {
                if (s[y] == 0) {
                    s[y] = 1;
                    self(self, y);
                }
            }
        };
        dfs(dfs, st);

        return s;
    };

    for (int x = 0; x < n; x++) {
        s[x] = search(x);
    }

    int k;
    std::cin >> k;
    Reach err{};
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        x -= 1;
        err[x] = 1;
    }

    for (int x = 0; x < n; x++) {
        for (int y = x + 1; y < n; y++) {
            if ((s[x] & s[y]) == err) {
                std::cout << x + 1 << ' ' << y + 1 << '\n';
                return 0;
            }
        }
    }

    std::cout << "-1\n";

    return 0;
}