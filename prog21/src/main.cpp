#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<pair<int, int>> vpii;

class DisjointSet {
private:
    vi raizes, rank, tamanho;
    int totalComponents;

public:
    DisjointSet(int n) {
        totalComponents = n;
        raizes.resize(n + 1);
        rank.resize(n + 1, 0);
        tamanho.resize(n + 1, 1);

        for (int i = 1; i <= n; ++i) {
            raizes[i] = i;
        }
    }

    int find(int x) {
        if (raizes[x] != x) {
            raizes[x] = find(raizes[x]);
        }
        return raizes[x];
    }

    bool merge(int i, int j) {
        int x = find(i);
        int y = find(j);

        if (x == y) return false;

        if (rank[x] > rank[y]) {
            raizes[y] = x;
            tamanho[x] += tamanho[y];
        } else if (rank[x] < rank[y]) {
            if (rank[x] == rank[y]) rank[x]++;
            raizes[x] = y;
            tamanho[y] += tamanho[x];
        } else {
            if (rank[x] == rank[y]) rank[y]++;
            raizes[y] = x;
            tamanho[x] += tamanho[y];
            rank[x]++;
        }
        totalComponents--;
        return true;
    }

    int getTamanho(int x) {
        return tamanho[find(x)];
    }

    int getTotalComponents() {
        return totalComponents;
    }
};

vpii obterEntradas(int N, int E) {
    vpii edges(E);
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }
    return edges;
}

int main() {
    int N, E;
    cin >> N >> E;

    vpii edges = obterEntradas(N, E);

    DisjointSet ds(N);

    int maiorComponent = 1;
    for (auto& edge : edges) {
        ds.merge(edge.first, edge.second);
        int maxComponentes = max(ds.getTamanho(edge.first), ds.getTamanho(edge.second));
        if (maiorComponent < maxComponentes) maiorComponent = maxComponentes;
        cout << ds.getTotalComponents() << " " << maiorComponent << endl;
    }

    return 0;
}
