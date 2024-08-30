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
typedef vector<vecInt> vecVecInt;

typedef struct {
  bool operator()(vecInt itemA, vecInt itemB) { 
    return itemA[0] != itemB[0] 
      ? itemA[0] > itemB[0]
      : itemA[1] != itemB[1]
      ? itemA[1] < itemB[1]
      : itemA[1] > itemB[1]; 
  }
} ordemTupla;

typedef priority_queue<vecInt, vecVecInt, ordemTupla> priorQueVecVecInt;

int contabilizarCustoMaximo(vecVecInt vecEntrada) {
  priorQueVecVecInt vecTempoOrdem;

  for (auto &x : vecEntrada) vecTempoOrdem.push(x);

  int tempoTranscorrido = 0;
  int custoTotal = 0;

  int N = vecEntrada.size();
  for (int x = 0; x < N; x++) {
    vecInt itemFila = vecTempoOrdem.top();
    int t = itemFila[0];
    int d = itemFila[1];

    tempoTranscorrido += t;
    custoTotal += d - tempoTranscorrido;
    vecTempoOrdem.pop();
  }

  return custoTotal;
}

vecVecInt obterVetorEntrada(int N) {
  vecInt duracaoLimite(2);
  vecVecInt vecEntrada;
  for (int i = 0; i < N; i++) {
    int t; int d;
    cin >> t;
    cin >> d;
    duracaoLimite[0] = t;
    duracaoLimite[1] = d;

    vecEntrada.push_back(duracaoLimite);
  }

  return vecEntrada;
}

/**
 * Construir lista de prioridades e executar consultas em sequencia
 */
int main() {

  int N;
  cin >> N;

  vecVecInt vecEntrada = obterVetorEntrada(N);

  int total = contabilizarCustoMaximo(vecEntrada);
  cout << total;

  return 0;
}