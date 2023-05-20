#include <bits/stdc++.h>
using namespace std;
#define DEBUG 0
#define st first
#define nd second

const int SZ = 2e3+7;
const int MV = 3e3+7;

int A[SZ], B[SZ];
int dp[SZ][MV][4];

/*
0 --> Left Forward
1 --> Right Forward
2 --> Left Backward
3 --> Right Backward
*/

void knapsack(int N, int M, bool sym) {
    int l = sym ? 2:0;
    int r = sym ? 3:1;
    int c = sym ? 1:-1;
    int start = sym ? N:1;
    int end = sym ? 0:N+1;

    // Knapsack 0/1
    for(int i=start;i!=end;i-=c) {
        if(A[i]>=0 && B[i]<0) { // (+,-)
            for(int j=0;j<=M;j++) {
                dp[i][j][l] = max(dp[i+c][j][l], j+B[i]>=0 ? dp[i+c][j+B[i]][l] + A[i] : 0);
                dp[i][j][r] = dp[i+c][j][r];
            }
        }
        else if(B[i]>=0 && A[i]<0) { // (-,+)
            for(int j=0;j<=M;j++) {
                dp[i][j][r] = max(dp[i+c][j][r], j+A[i]>=0 ? dp[i+c][j+A[i]][r] + B[i] : 0);
                dp[i][j][l] = dp[i+c][j][l];
            }
        }
        else if(A[i]>=0 && B[i]>=0) { // (+,+)
            for(int j=0;j<=M;j++) {
                dp[i][j][l] = dp[i+c][j][l] + A[i];
                dp[i][j][r] = dp[i+c][j][r] + B[i];
            }
        }
        else {
            for(int j=0;j<=M;j++) { // (-,-)
                dp[i][j][l] = dp[i+c][j][l];
                dp[i][j][r] = dp[i+c][j][r];
            }
        }
    }
}

int main() {
    int N, M, S;
    cin >> N >> M >> S;
    for(int i=1;i<=N;i++) cin >> A[i];
    for(int i=1;i<=N;i++) cin >> B[i];

    assert(N>=1 && M>=0);

    knapsack(N, M, false); // Forward
    knapsack(N, M, true); // Backward

    int result = dp[N][M][0] + dp[N][M][1]; // default - not swap yet
    
    if(!S) {
        cout << result;
        return 0;
    }

    // swap check
    for(int i=1;i<N;i++) {
        int best_left = 0;
        int best_right = 0;
        for(int j=0;j<=M;j++) {
            best_left = max(best_left, dp[i][j][0] + dp[i+1][M-j][3]);
            best_right = max(best_right, dp[i][j][1] + dp[i+1][M-j][2]);
        }
        result = max(result, best_left + best_right);
    }

    cout << result;

    return 0;
}