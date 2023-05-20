#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define pii pair<int, int>
#define pII pair<pii, pii>
#define pll pair<long long, long long>
#define ll long long
#define ld long double
#define st first
#define nd second
#define pb push_back
#define INF INT_MAX
#define sz(x) x.size()
using namespace std;

const int N = 1e5 + 10;

pair<pll, pll> line[N];

bool cmp(pair<pll, pll> a, pair<pll, pll> b) {
    pll cur_a = a.nd;
    pll cur_b = b.nd;
    return cur_b.st*cur_a.nd < cur_a.st*cur_b.nd;
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        ll x, y, z, w; cin >> x >> y >> z >> w;
        if (y*z > w*x) swap(x, z), swap(y, w);
        line[i] = {{x, y}, {z, w}};
    }
    sort(line+1, line+n+1, cmp);
    int cnt = n;
    pll cur = {1, -1};
    for (int i = 1; i <= n; ++i) {
        auto [x, y] = line[i].st;
        if (cur.nd*x >= cur.st*y) continue;
        cnt--;
        cur = line[i].nd;
    }
    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
