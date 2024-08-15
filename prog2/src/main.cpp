#include <iostream>
#include <queue>
#include <map>

using namespace std;
typedef priority_queue<int, vector<int>, greater<int>> filaPriorInt;
typedef map<int, filaPriorInt> mapIntFila;

mapIntFila mif;

void mapearTempoFila(int N) {
  for (int i = 0; i < N; i++) {
    string query;
    cin >> query;

    int id;
    cin >> id;

    int tempo;
    cin >> tempo;

    mif[tempo].push(id);
  }
}

void obter(int buscas) {
  int t = 1;
  int obtidos = 0;
  while (buscas > obtidos) {

    filaPriorInt cpFila2;
    for (auto& [k,v] : mif) {
      filaPriorInt cpFila = v;
      if (t % k == 0) {
        while (!cpFila.empty()) {
          cpFila2.push(cpFila.top());
          cpFila.pop();
        }
      }
    }

    while (!cpFila2.empty() && buscas > obtidos) {
      cout << cpFila2.top() << endl;
      cpFila2.pop();
      obtidos++;
    }

    t++;
  }
}

int main() {

  int N;
  cin >> N;

  mapearTempoFila(N);

  int buscas;
  cin >> buscas;
  obter(buscas);

  return 0;
}