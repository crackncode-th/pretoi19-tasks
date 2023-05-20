#include <bits/stdc++.h>
using namespace std;
string letter, S;
vector<int> adj[500005];
priority_queue<int, vector<int>, greater<int>> best_pos[26];
int dist[500005];

int main(int argc, char* argv[]){
  ios_base::sync_with_stdio(0); cin.tie(0);

  int N, M, K; cin >> N >> M >> K;
  cin >> letter;

  for(int i = 1, u, v; i <= M; i++){
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  queue<int> q; dist[1] = 1;
  q.push(1);
  while(!q.empty()){
    int n = q.front(); q.pop();
    for(auto x : adj[n]){
      if(dist[x]) continue;
      dist[x] = dist[n] + 1;
      q.push(x);
    }
  }
  for(int i = 1; i <= N; i++) best_pos[letter[i - 1] - 'A'].push(dist[i] - 1);

  long long ans = 0;
  cin >> S;
  for(auto x : S){
    if(best_pos[x - 'A'].empty()){
      printf("-1\n"); return 0;
    }
    ans += (best_pos[x - 'A'].top() * 1ll);
    best_pos[x - 'A'].pop();
  }
  printf("%lld\n", ans << 1);
  return 0;
}