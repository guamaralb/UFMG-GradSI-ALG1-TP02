#include <iostream>
#include <queue>

using namespace std;

const int MAX_V = 100; // Maximum number of vertices in the graph

class HopcroftKarp {
    int m, n; // Number of vertices in left and right sets
    int graph[MAX_V][MAX_V]; // Adjacency matrix representation of the graph
    int matchL[MAX_V], matchR[MAX_V]; // Stores the matching pairs
    int dist[MAX_V]; // Stores the distance of each vertex from source

public:
    HopcroftKarp(int m, int n) {
        this->m = m;
        this->n = n;

        // Initialize graph with zeros
        for (int i = 0; i < MAX_V; i++) {
            for (int j = 0; j < MAX_V; j++) {
                graph[i][j] = 0;
            }
        }

        // Initialize matchL and matchR with zeros
        for (int i = 0; i < MAX_V; i++) {
            matchL[i] = 0;
            matchR[i] = 0;
        }

        // Initialize dist with zeros
        for (int i = 0; i < MAX_V; i++) {
            dist[i] = 0;
        }
    }

    void addEdge(int u, int v) {
        graph[u][v] = 1;
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= m; u++) {
            if (matchL[u] == 0) {
                dist[u] = 0;
                q.push(u);
            }
            else {
                dist[u] = MAX_V; // Using a large value as infinity
            }
        }
        dist[0] = MAX_V;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (dist[u] < dist[0]) {
                for (int v = 1; v <= n; v++) {
                    if (graph[u][v] && dist[matchR[v]] == MAX_V) {
                        dist[matchR[v]] = dist[u] + 1;
                        q.push(matchR[v]);
                    }
                }
            }
        }

        return dist[0] != MAX_V;
    }

    bool dfs(int u) {
        if (u == 0) {
            return true;
        }

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }

        dist[u] = MAX_V;
        return false;
    }

    int maximumMatching() {
        int matching = 0;

        while (bfs()) {
            for (int u = 1; u <= m; u++) {
                if (matchL[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }

        return matching;
    }
};
