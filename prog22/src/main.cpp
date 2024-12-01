#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

typedef vector<list<int>> vli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef stack<int> si;

void dfs1(int node, vb& visitados, si& pilhaFinal, const vli& adjList) {
    visitados[node] = true;
    for (int prox : adjList[node]) {
        if (!visitados[prox]) {
            dfs1(prox, visitados, pilhaFinal, adjList);
        }
    }
    pilhaFinal.push(node);
}

void dfs2(int node, vb& visitados, vi& component, const vli& invAdjList) {
    visitados[node] = true;
    component.push_back(node);
    for (int prox : invAdjList[node]) {
        if (!visitados[prox]) {
            dfs2(prox, visitados, component, invAdjList);
        }
    }
}

// SCCs via Kosaraju
vvi getSCCs(const vli& adjList) {
    int n = adjList.size() - 1;
    vb visitados(n + 1, false);
    si pilhaFinal;

    for (int i = 1; i <= n; ++i) {
        if (!visitados[i]) {
            dfs1(i, visitados, pilhaFinal, adjList);
        }
    }

    // Inverter arestas
    vli invAdjList(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (int v : adjList[u]) {
            invAdjList[v].push_back(u);
        }
    }

    fill(visitados.begin(), visitados.end(), false);
    vvi SCCs;

    while (!pilhaFinal.empty()) {
        int node = pilhaFinal.top();
        pilhaFinal.pop();

        if (!visitados[node]) {
            vi component;
            dfs2(node, visitados, component, invAdjList);
            SCCs.push_back(component);
        }
    }

    return SCCs;
}

vli construirAdjList() {
    int nodes, edges;
    cin >> nodes >> edges;

    vli adjList(nodes + 1);

    if (nodes == 0 && edges == 0)
        return adjList;

    for (int i = 0; i < edges; ++i) {
        int u, v, type;
        cin >> u >> v >> type;

        adjList[u].push_back(v);

        if (type == 2) {
            adjList[v].push_back(u);
        }
    }

    return adjList;
}

int obterAmorTotal(vvi sccs) {
    if (sccs.size() == 1) return 1;
    return 0;
}

int main() {
    while (true) {
        vli adjList = construirAdjList();
        if (adjList.size() == 1) break;

        vvi sccs = getSCCs(adjList);
        cout << obterAmorTotal(sccs) << endl;
    }

    return 0;
}
