#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#define N_MAX_PRIMOS 10000000

using namespace std;

typedef vector<long long int> vi;
typedef vector<vi> v2i;

v2i obterMatrizEntrada(int N, int M) {
  v2i matrizEntrada(N, vi(M, -1));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int val;
      cin >> val;
      matrizEntrada[i][j] = val;
    }
  }
  return matrizEntrada;
}

bitset<N_MAX_PRIMOS> montarCrivoPrimos(long long int maxPrimos){
  bitset<N_MAX_PRIMOS> crivo;
	crivo.set();

	crivo[0] = crivo[1] = 0;

	for (long long int i = 2; i <= maxPrimos + 1; ++i){
		if (crivo[i]){
			for (long long int j = i*i; j <= maxPrimos + 1; j += i)
				crivo[j]=0;
		}
	}

  return crivo;
}

void printMatriz(v2i matrizEntrada) {
  for (auto &x : matrizEntrada) {
    for (auto &y : x) cout << y << " ";
    cout << endl;
  }
}

int obterMenorNumeroOperacoes(v2i matrizEntrada, bitset<N_MAX_PRIMOS> crivo) {

  int M = matrizEntrada.size();
  int N = matrizEntrada[0].size();

  v2i matrizNumeroOps(M, vi(N, 0));
  vi totalOpsPorLinha;
  for (int i = 0; i < M; i++) {
    long long int totalOps = 0;
    for (int j = 0; j < N; j++) {
      long long int original = matrizEntrada[i][j];
      while (!crivo[original]) {
        original++;
        matrizNumeroOps[i][j] += 1;
        totalOps++;
      }
    }
    totalOpsPorLinha.push_back(totalOps);
  }
  // for (auto &x : totalOpsPorLinha) cout << x << " ";
  // cout << endl;

  long long int minLinha = min_element(totalOpsPorLinha.begin(), totalOpsPorLinha.end())[0];

  vi totalOpsPorColuna;
  for (int i = 0; i < N; i++) {
    long long int totalOps = 0;
    for (int j = 0; j < M; j++) {
      totalOps += matrizNumeroOps[j][i];
    }
    totalOpsPorColuna.push_back(totalOps);
  }

  long long int minColuna = min_element(totalOpsPorColuna.begin(), totalOpsPorColuna.end())[0];

  return min(minLinha, minColuna);
}

int main(void) {

  int N, M;
  cin >> N;
  cin >> M;

  bitset<N_MAX_PRIMOS> crivo = montarCrivoPrimos(N_MAX_PRIMOS);

  v2i matrizEntrada = obterMatrizEntrada(N, M);

  // printMatriz(matrizEntrada);
  // cout << endl;
  cout << obterMenorNumeroOperacoes(matrizEntrada, crivo);

  return 0;
}