#include <bits/stdc++.h>
using namespace std;
long long A[100001], B[100001], X[100001];
long long cnt_inv = 0;

void merge(int l, int r, int mid){
  vector<long long> L, R;
  for(int i = l; i <= mid; i++) L.push_back(X[i]);
  for(int i = mid + 1; i <= r; i++) R.push_back(X[i]);
  
  int lidx = 0, ridx = 0, idx = l;
  while(lidx < L.size() && ridx < R.size()){
    if(L[lidx] > R[ridx]) X[idx++] = L[lidx++];
    else{
      cnt_inv += (L.size() - lidx) * 1ll;
      X[idx++] = R[ridx++];
    }
  }
  while(ridx < R.size()) X[idx++] = R[ridx++];
  while(lidx < L.size()) X[idx++] = L[lidx++];
}

void count_inversion(int l, int r){
  if(l == r) return;

  int mid = (l + r) >> 1;
  count_inversion(l, mid);
  count_inversion(mid + 1, r);
  merge(l, r, mid);
}

int main(int argc, char* argv[]){
  long long N, K;
  scanf("%lld %lld", &N, &K);
  for(int i = 1; i <= N; i++){
    scanf("%lld", &A[i]);
    A[i] *= (1000 * 1ll);
  }
  for(int i = 1; i <= N; i++) scanf("%lld", &B[i]);

  long long L = 1, R = 1e7;
  while(L < R){
    long long mid = (L + R + 1) >> 1;
    X[0] = 0;
    for(int i = 1; i <= N; i++) 
      X[i] = A[i] - (mid * B[i]) + X[i - 1];

    cnt_inv = 0;
    count_inversion(0, N);

    if(cnt_inv >= K) L = mid;
    else R = mid - 1;
  }
  double ans = double(L) / double(1000);
  printf("%.3lf", ans);
  return 0;
}
