/**
 * Projeto 3: Limpeza de Vetor
 * 
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <queue>
#include <map>

using namespace std;
typedef vector<int> vecInt;
typedef map<int,int> mapIntInt;

mapIntInt previo;

int totalizarLimpezas(vecInt vecEntrada) {
  int N = vecEntrada.size() + 1;
  int total = 0;
  vecInt vecPosicoes(N, 0);
  for (int i = 1; i < N; i++) {
    int v = vecEntrada[i-1];
    if (previo[v-1]) {
      previo[v] = 1;
      continue;
    }
    previo[v] = 1;
    total++;
  }
  return total;
}

vecInt obterVetorEntrada(int N) {
  vecInt vecEntrada(N, 0);
  for (int i = 0; i < N; i++) {
    int v;
    cin >> v;
    vecEntrada[i] = v;
  }

  return vecEntrada;
}

/**
 * Construir lista de prioridades e executar consultas em sequencia
 */
int main() {

  int N;
  cin >> N;

  vecInt vecEntrada = obterVetorEntrada(N);

  int total = totalizarLimpezas(vecEntrada);
  cout << total;

  return 0;
}