#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>

std::vector<int> dijkstras(const std::vector<std::vector<int>> edges, int start, int n) {
    // init dist and queue
    const int INF = 1e9;
    std::vector<std::vector<std::pair<int, int>>> adj(n);

    for (auto& edge: edges) {
        int s = edge[0], e = edge[1], w = edge[2];
        adj[s].emplace_back(w, e);
    }

    std::vector<int> dist(n, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, i] = pq.top();
        pq.pop();

        if (d > dist[i]) {
            continue;
        }
        
        for (const auto& [w, e] : adj[i]) {
            if (dist[i] + w < dist[e]) {
                dist[e] = dist[i] + w;
                pq.push({dist[e], e});
            }
        }
    }

    return dist;
    
};

std::vector<int> bellman_ford(const std::vector<std::vector<int>> edges, int start, int n) {
    // initialize dist array
    const int INF = 1e9;
    std::vector<int> dist(n, INF);
    dist[start] = 0;

    // iterate through edges n - 1 times and relax edges
    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            int s = edge[0], e = edge[1], w = edge[2];
            if (dist[s] != INF) {
                if (dist[s] + w < dist[e]) {
                    dist[e] = dist[s] + w;
                }
            }
        }
    }

    // iterate one more time to detect negative cycles
    for (auto& edge: edges) {
        int s = edge[0], e = edge[1], w = edge[2];
        if (dist[s] != INF) {
            if (dist[s] + w < dist[e]) {
                std::cout << "negative cycle detected";
                return std::vector<int>();
            }
        }
    }

    // return dist array
    return dist;
}

class UnionFind {
private:
    std::vector<int> arr;
    std::vector<int> rank;
public:
    UnionFind(int n) {
        for (int i = 0; i < n; i++) {
            arr.emplace_back(i);
        }
        rank.resize(n, 1);
    }

    int find(int e) {
        if (arr[e] != e) {
            arr[e] = find(arr[e]);
        }
        return arr[e];
    }

    void union_find(int e1, int e2) {
        int p1 = find(e1), p2 = find(e2);
        if (p1 == p2) {
            return;
        }

        if (rank[p1] > rank[p2]) {
            arr[p2] = p1;
        } else if (rank[p1] < rank[p2]) {
            arr[p1] = p2;
        } else {
            arr[p2] = p1;
            rank[p1]++;
        }
        return;
    }
};

std::vector<std::vector<int>> kruskals(const std::vector<std::vector<int>> edges, int n) {
    // create union find data structure, heap with edges
    UnionFind uf(n);
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
    for (const auto& edge : edges) {
        pq.push({edge[2], edge[0], edge[1]});
    }
    std::vector<std::vector<int>> res;

    // iterate until mst is finished 
    while (res.size() < n - 1 && !pq.empty()) {
        auto edge = pq.top();
        pq.pop();
        int w = edge[0], s = edge[1], e = edge[2];
        if (uf.find(s) != uf.find(e)) {
            uf.union_find(s, e);
            res.push_back(std::vector<int>{s, e, w});
        }
        
    }
    return res;
}

int main() {
    int n = 4, start = 0;

    // ---------- Dijkstra's Test ----------
    std::cout << "Dijkstra's shortest paths from node " << start << ":" << std::endl;
    std::vector<std::vector<int>> dijkstra_edges = {
        {0, 1, 4}, {0, 2, 1}, {2, 1, 2}, {1, 3, 1}, {2, 3, 5}
    };
    std::vector<int> dist = dijkstras(dijkstra_edges, start, n);
    for (int i = 0; i < dist.size(); i++) {
        std::cout << "Node " << i << ": " << dist[i] << std::endl;
    }
    std::cout << std::endl;

    // ---------- Bellman-Ford Test ----------
    std::cout << "Bellman-Ford shortest paths (with negative cycle check):" << std::endl;
    std::vector<std::vector<int>> bf_edges = {
        {0, 1, 1}, {1, 2, -1}, {2, 3, -1}, {3, 1, -1}
    };
    dist = bellman_ford(bf_edges, start, n);
    if (!dist.empty()) {
        for (int i = 0; i < dist.size(); i++) {
            std::cout << "Node " << i << ": " << dist[i] << std::endl;
        }
    }
    std::cout << std::endl;

    // ---------- Kruskal's MST Test ----------
    std::cout << "Kruskal's MST edges (start, end, weight):" << std::endl;
    std::vector<std::vector<int>> kruskals_edges = {
        {0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 5}, {2, 3, 3}
    };
    auto mst = kruskals(kruskals_edges, n);
    for (const auto& edge : mst) {
        std::cout << edge[0] << " — " << edge[1] << " (weight " << edge[2] << ")" << std::endl;
    }

    return 0;
}