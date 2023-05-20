#include<bits/stdc++.h>
//#include "grader.h"
#define pii pair<int, int>
#define pll pair<long long, long long>
#define ll long long
#define ld long double
#define st first
#define nd second
#define pb push_back
#define INF INT_MAX
using namespace std;

const int maxN = 1e5 + 10;
ll A[maxN], B[maxN], C[maxN], fw[maxN];

void update(int i) {for (; i < maxN; i += i&-i) fw[i]++;}
int query(int i) {int ret=0; for (; i > 0; i -= i&-i) ret += fw[i]; return ret;}

ll count_inversion(int N) {
    map<ll, ll> mp;
    mp[0] = 0;
    ll cnt = 0, cnt_inv = 0;
    for (int i = 1; i < maxN; ++i) fw[i] = 0;
    for (int i = 1; i <= N; ++i) mp[C[i]] = 0;
    for (auto [i, j] : mp) mp[i] = ++cnt;
    for (int i = N; i >= 1; --i) {
        update(mp[C[i]]);
        cnt_inv += query(maxN-1) - query(mp[C[i-1]]-1);
    }
    return cnt_inv;
}

void solve() {
    ll N, K; cin >> N >> K;
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];
    ll l = 0, r = 1e7;
    while (l < r) {
        ll mid = (l+r+1)/2;
        for (int i = 1; i <= N; ++i) C[i] = C[i-1] + 1000*A[i] - mid*B[i];
        if (count_inversion(N) >= K) l = mid;
        else r = mid-1;
    }
    printf("%.3f\n", (double)l/1000);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
