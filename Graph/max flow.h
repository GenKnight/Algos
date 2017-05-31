// An implementation of Dinic's algorithm
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)(n);++i)
#define FOR(i,b,e) for(ll i=b;i<=(ll)(e);++i)
#define FORR(i,b,e) for(ll i=b;i>=(ll)(e);--i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define all(a) a.begin(),a.end()
template<typename T1, typename T2> void Max(T1& a, T2 b) { a = max(a, (T1)b); }
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }

struct MaxFlow {
  static const int inf = 1e9;

  vector<int> last, used, level, q, cap, to, prev;
  int n, qi, qj;

  // _n: number of vertexes
  // m: number of edges
  void init(int _n, int m=0) {
    n = _n;
    last.assign(n, -1);
    q.resize(n);
    cap.clear();
    to.clear();
    prev.clear();
    if(m>0){
      cap.reserve(m*2);
      to.reserve(m*2);
      prev.reserve(m*2);
    }
  }

  // c2: capacity on reverse edge y->x,
  // if edge y->x should never be used(e.g: to source or from sink or for vertex capacity),
  // then set c2 to -1 to speed up algo by removing the reverse edge from the graph
  void add(int x, int y, int c, int c2 = 0) {
    prev.push_back(last[x]);
    last[x] = cap.size();
    cap.push_back(c);
    to.push_back(y);

    prev.push_back(last[y]);
    if(c2>=0) last[y] = cap.size();
    else c2=0; // make it easier to clear flow
    cap.push_back(c2);
    to.push_back(x);
  }

  bool bfs(int s, int t) {
	level.assign(n,-1);
    qi = qj = 0;
    level[s] = 0;
    q[qj++] = s;
    while (qi < qj) {
      int cur = q[qi++];
      int next_level = level[cur] + 1;
      for (int i = last[cur]; i >= 0; i = prev[i]) if (level[to[i]] == -1 && cap[i]) {
        level[to[i]] = next_level;
        if (to[i] == t) return 1;
        q[qj++] = to[i];
      }
    }
    return 0;
  }

  int dfs(int v, int t, int maxf) {
    if (v == t) return maxf;
    int f = 0;
    for (int i = used[v]; i >= 0; used[v] = i = prev[i]) if (level[to[i]] > level[v] && cap[i]) {
      int ret = dfs(to[i], t, min(maxf - f, cap[i]));
      cap[i] -= ret;
      cap[i ^ 1] += ret;
      if ((f += ret) == maxf) break;
    }
    return f;
  }

  int maxFlow(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
	  used = last;
      ans += dfs(s, t, inf);
    }
    return ans;
  }

}; mf;
