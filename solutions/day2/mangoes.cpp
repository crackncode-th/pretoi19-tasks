#include <bits/stdc++.h>
using namespace std;
int qs[5005][5005];
vector<array<int, 3>> v;
int main(int argc, char* argv[]){
  int N, M, R, C;
  scanf("%d %d %d %d", &N, &M, &R, &C);
  for(int i = 1, r, c, w; i <= N; i++){
    scanf("%d %d %d", &r, &c, &w);
    v.push_back({r, c, w});
  }
  for(int i = 1, x, y; i <= M; i++){
    scanf("%d %d", &x, &y); qs[x][y]++;
  }
  for(int i = 1; i <= R; i++){
    for(int j = 1; j <= C; j++){
      qs[i][j] += qs[i - 1][j] + qs[i][j - 1] - qs[i - 1][j - 1];
    }
  }

  int l = 1, r = max(R, C);
  while(l < r){
    int mid = (l + r) >> 1;
    bool ok = true;
    for(auto [x, y, w] : v){
      int x1 = max(0, x - mid - 1), y1 = max(0, y - mid - 1);
      int x2 = min(R, x + mid), y2 = min(C, y + mid);
      if(qs[x2][y2] - qs[x2][y1] - qs[x1][y2] + qs[x1][y1] < w){
        ok = false;
        break;
      }
    }
    if(ok) r = mid;
    else l = mid + 1;
  }
  printf("%d\n", l);
  return 0;
}
