#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int vec_min(vector<int>& V) {
    if (V.size()) {
        int m = V[0];
        for (int x : V) {
            if (x < m)
                m = x;
        }
        return m;
    }
    return 0;
}

namespace std {
    ostream& operator << (ostream& os, vector<int> V) {
        for (int i = 1; i < V.size(); i++) {
            os << V[i];
            if (i < V.size() - 1)
                os << ' ';
        }
        return os;
    }
};

bool comparator(int a, int b) {
    return a >= b;
}

class BiGraph {
public:
    int m, n;
    vector<int> dist;
    vector<int> pairU;
    vector<int> pairV;
    vector<vector<int>> adj;
    //vector<pair<bool,bool>> blocked;
    vector<bool> blocked;
    vector<vector<char>> direct;
    bool BFS();
    pair<int,vector<int>&> BFS(int u);
    bool DFS(int u);
    vector<int> lex_min();
    vector<int> Hopcroft_Karp();
    BiGraph(int _m = 0, int _n = 0) : m(_m), n(_n) {
        this->adj = vector<vector<int>>(2*_m + 1);
        this -> direct = vector<vector<char>>(2*_m + 1,vector<char>(2*_m + 1,'-'));
    }
};

//class DirBiGraph {
//public:
//    int N;
//    vector<int> M;
//    vector<int> lex_min();
//    vector<vector<int>> adj;
//    vector<vector<bool>> direct;
//    vector<vector<bool>> blocked;
//    pair<vector<int>,vector<char>> BFS(int u);
//    DirBiGraph(BiGraph& G) {
//        this -> N = G.m;
//        this -> adj = vector<vector<int>>(2*G.m + 1);
//        for (int i = 1; i <= G.m; i++) {
//            for (int x : G.adj[i]) {
//                if (direct[i][x] == false) {
//                    this -> adj[i].push_back(x);
//                }
//                else {
//
//                }
//            }
//        }
//    }
//};

bool BiGraph::BFS() {
    queue<int> Q;
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            Q.push(u);
        }
        else {
            dist[u] = INT_MAX;
        }
    }
    dist[0] = INT_MAX; //dist[NIL] = INF

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        if (dist[u] < dist[0]) {
            for (int v : adj[u]) {
                if (dist[pairV[v - m]] == INT_MAX) {
                    dist[pairV[v - m]] = dist[u] + 1;
                    Q.push(pairV[v - m]);
                }
            }
        }
    }
    return dist[0] != INT_MAX;
}
vector<int> get_path() {
    vector<int> path;
    return path;
}


bool BiGraph::DFS(int u) {
    if (u != 0) {
        for (int v : adj[u]) {
            if (dist[pairV[v - m]] == dist[u] + 1) {
                if (DFS(pairV[v - m]) == true) {
                    pairV[v - m] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    return true;
}

vector<int> BiGraph::Hopcroft_Karp() {
    pairU = vector<int>(m + 1, 0);
    pairV = vector<int>(n + 1, 0);
    dist = vector<int>(m + 1);
    int res = 0;
    while (BFS()) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 and DFS(u)) {
                res++;
            }
        }
    }
    return pairU;
}

vector<int> BiGraph:: lex_min() {
    //vector<bool> lockedX(m + 1,false);
    //int X = m;
    //vector<bool> lockedY(m + 1,false);
    //int Y = m;
    //blocked = vector<pair<bool,bool>> (m + 1, {false,false});
    //blocked = vector<vector<pair<bool,bool>>> (m + 1,vector<pair<bool,bool>>(m + 1,{false,false}));
    blocked = vector<bool>(2*m + 1,false);
    for (int i = 1; i <= m; i++) {
        direct[i][pairU[i]] = '+';
    }
    for (int i = 1; i <= m; i++) {
        for (int x : adj[i]) {
            if (direct[i][x] == '-') {
                adj[x].push_back(i);

            }
        }
    }
    int unblock = m;
    int u = 1;
    while (unblock > 1) {
        pair<int,vector<int>&> p1 = BFS(u);
        int v = p1.first;
        vector<pair<int,int>> C(p1.second.size());
        for (int i = 0; i < p1.second.size(); i++) {
            if (p1.second[i] - p1.second[i + 1] % (p1.second.size()) >= 0) {
                C[i] = {p1.second[(i + 1) % p1.second.size()], p1.second[i]};
            } else {
                C[i] = { p1.second[i], p1.second[(i + 1) % p1.second.size()]};
            }
        }
        vector<bool> change(C.size(),true);
        int size = C.size();
        for (int i = 0; i < size; i++) {
            for (int j = 1; j <= m; j++) {
                if (j == C[i].first and pairU[j] == C[i].second) {
                    change[i] = false;
                }
                else {
                    C.push_back({j,pairU[j]});
                }
            }
        }
        blocked[u] = true;
        blocked[v] = true;
        unblock--;
        u++;
    }
    //int v = vec_min(YuPar.first);
}

pair<int,vector<int>&> BiGraph:: BFS(int s) {
    vector<char> color(2*m + 1,'w');
    vector<int> d(2*m + 1, INT_MAX);
    vector<int> par(2*m + 1, -1);
    vector<int> Ys;
    color[s] = 'g';
    dist[s] = 0;
    queue<int> Q;
    Q.push(s);
    //int side = 0; // if even - we are on the left size, else : on the right if odd;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        //side++;
        for (int v : adj[u]) {
            //if (blocked[v] == false and color[v] == 'w' and ((direct[u][v] == true and side % 2 == 0) or (direct[u][v] == false and side % 2 == 1))) {
            if (blocked[v] == false and color[v] == 'w') {
                if ((u <= m and direct[u][v] == '+') or (u >= m + 1 and direct[u][v] == '-')) {
                    //if (color[v] == 'w') {
                    color[v] = 'g';
                    dist[v] = dist[u] + 1;
                    par[v] = u;
                    Q.push(v);
                    bool is_reacheable = false;
                    for (int x : adj[s]) {
                       if (x == v) {
                          is_reacheable = true;
                          break;
                        }
                    }
                    if (is_reacheable)
                        Ys.push_back(v);
                }
            }
        }
        color[u] = 'b';
    }

    vector<int> path;
    int to = vec_min(Ys); //v irzh
    for (int v = to; v!= -1; v = par[v])
        path.push_back(v);

    return {to,path};
}

int main() {
    int N;
    ifstream fin("input.in");
    fin >> N;
   // int P = 1;
    vector<int> Arr(N*N + 1);
    vector<vector<int>> C(N + 1,vector<int>(N + 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            fin >> C[i][j];
            Arr[N*(i - 1) + j] = C[i][j];
        }
    }
    fin.close();

    sort(Arr.begin() + 1,Arr.end(), comparator);
    vector<pair<BiGraph,pair<vector<int>,int>>> matchings;
    for (int i = 1; i <= N*N; i++) {
        if (i >= 1 or (i > 1 and Arr[i] > Arr[i - 1])) {
            int P = Arr[i];
            BiGraph G(N, N);
            for (int j = 1; j <= N; j++) {
                for (int k = 1; k <= N; k++) {
                    if (C[j][k] >= P) {
                        G.adj[j].push_back(k + N);
                    }
                }
            }
            vector<int> match = G.Hopcroft_Karp();
            if (match.size() == N + 1) {
                bool is_zeros = false;
                for (int z = 1; z <= N; z++)
                    if (match[z] == 0) {
                        is_zeros = true;
                        break;
                    }
                if (is_zeros == false) {
                    //if (matchings.size() and matchings[0].second.second > P)
                      //  break;
                    matchings.push_back({G,{match,P}});
                    break;
                }
            }
        }
    }

    //BiGraph G(2*N + 1,2*N + 1);
    cout << matchings[0].second.first;
   // for (pair<vector<int>,int> x : matchings) {
    //    cout << x.second << " : " << x.first << '\n';
    //}
   // cout << Arr << '\n' << matchings[0].first.pairU;

   //for (int x : matchings[0].first.adj[3])
       //cout << x << ' ';

    return 0;
}

