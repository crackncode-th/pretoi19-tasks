#include <bits/stdc++.h>
#define MAXN 50000
using namespace std;
int tour_group[100100], szidx[100100], gcnt[100100];
vector<pair<int, int>> mark[100100];
vector<pair<int, int>> edge;
int pa[100100][320], blocked[100100][320];
vector<int> allsz;
bitset<100100> szchk;

int findpa(int i, int a){
  return pa[a][i] == a ? a : pa[a][i] = findpa(i, pa[a][i]);
}

void union_range(int p, int l, int r){
  // Union edge #p for all group from index l to r
  int i = lower_bound(allsz.begin(), allsz.end(), l) - allsz.begin();
  for(; i < allsz.size() && allsz[i] <= r; i++){
    blocked[p][i]--;
    if(blocked[p][i]) continue;
    int gsz = allsz[i];

    auto [u, v] = edge[p];
    int pa_u = findpa(i, u), pa_v = findpa(i, v);
    if(pa_u != pa_v) pa[pa_u][i] = pa_v;
  }
}

int main(int argc, char* argv[]){
  int N, M, K, Q;
  scanf("%d %d %d %d", &N, &M, &K, &Q);

  // Collect how many tour groups and how many people,
  // Guaranteed to be lesser than sqrt(N)
  for(int i = 0, A; i < K; i++){
    scanf("%d", &A);
    tour_group[A]++;
  }
  for(int i = 1; i <= 100000; i++){
    if(!szchk[tour_group[i]]){
      szchk[tour_group[i]] = 1;
      allsz.push_back(tour_group[i]);
    }
    if(tour_group[i]) gcnt[tour_group[i]]++;
  }
  sort(allsz.begin(), allsz.end());

  // Construct initial graph
  edge.push_back({0, 0});
  for(int i = 1, u, v; i <= M; i++){
    scanf("%d %d", &u, &v);
    edge.push_back({u, v});
  }

  // Collect query
  vector<array<int, 4>> query;
  for(int i = 1; i <= Q; i++){
    int q; scanf("%d", &q);
    if(q == 1){
      int p, l, r; scanf("%d %d %d", &p, &l, &r);
      query.push_back({q, p, l, r});
      mark[p].push_back({l, r});
    }
    else{
      int s, e; scanf("%d %d", &s, &e);
      query.push_back({q, s, e, 0});
    }
  }

  // Add blocked layers for blocked edges
  for(int i = 1; i <= M; i++){
    for(auto [l, r] : mark[i]){
      int lidx = lower_bound(allsz.begin(), allsz.end(), l) - allsz.begin();
      int ridx = upper_bound(allsz.begin(), allsz.end(), r) - allsz.begin();
      blocked[i][lidx] += 1;
      blocked[i][ridx] -= 1;
    }
  }

  // Init DSU
  for(int i = 1; i <= N; i++)
    for(int j = 1; j < allsz.size(); j++) pa[i][j] = i;

  for(int i = 1; i <= M; i++){
    for(int j = 1; j < allsz.size(); j++){
      blocked[i][j] += blocked[i][j - 1];

      // Union all edges that can travel by default
      if(!blocked[i][j]){
        auto [u, v] = edge[i];
        pa[findpa(j, u)][j] = findpa(j, v);
      }
    }
  }

  // Start answering query from back to front
  stack<int> ans;
  for(int i = query.size() - 1; i >= 0; i--){
    int q = query[i][0];
    if(q == 1){
      int p = query[i][1], l = query[i][2], r = query[i][3];
      union_range(p, l, r);
    }
    else{
      int s = query[i][1], e = query[i][2], total_cnt = 0;
      for(int j = 1; j < allsz.size(); j++){
        if(findpa(j, s) == findpa(j, e))
          total_cnt += gcnt[allsz[j]];
      }
      ans.push(total_cnt);
    }
  }

  // Print all answers
  while(!ans.empty()){
    printf("%d\n", ans.top());
    ans.pop();
  }
  return 0;
}
