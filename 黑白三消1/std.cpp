#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    // 0 1

    int cnt[2] = {n, m};
    
    std::string s;

    auto add = [&](int c) {
        s.push_back(c + '0');
        cnt[c] -= 1;
    };

    for (int i = 0; i < n + m; i++) {
        if (s.size() >= 2 and s.back() == s[s.size() - 2]) {
            int c = s.back() - '0';
            if (cnt[c ^ 1] == 0) {
                std::cout << "-1\n";
                return 0;
            } else {
                c ^= 1;
                add(c);
            }
        } else {
            if (cnt[0] > cnt[1]) {
                add(0);
            } else {
                add(1);
            }
        }
    }

    std::cout << s << '\n';

    return 0;
}