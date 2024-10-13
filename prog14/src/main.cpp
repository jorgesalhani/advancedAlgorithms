#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> v2i ;

v2i obterEntradas(int N) {

  v2i matrizMapa(N, vi(N, 0));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int distI;
      cin >> distI;
      matrizMapa[i][j] = distI;
    }
  }

  return matrizMapa;
}

void printV2i(v2i &matriz) {
  for (auto &x : matriz) {
    for (auto &y : x) cout << y << " ";
    cout << endl;
  }
  cout << endl;
}

void printV2Bitmask(v2i &matriz) {
  for (auto &x : matriz) {
    for (auto &y : x) cout << bitset<8>(y) << " ";
    cout << endl;
  }
  cout << endl;
}

int obterMenorCaminhoHamilt(int cidInicial, int bitmask, int pos, v2i& mapa, v2i& memo) {
    int N = mapa.size();
    
    // cout << bitset<8>(bitmask) << endl;

    if (bitmask == (1 << N) - 1) return mapa[pos][cidInicial];
    if (memo[bitmask][pos] != -1) return memo[bitmask][pos];


    int menorProxCidade = INT32_MAX;

    for (int k = 0; k < N; ++k) {
      int visitaK = 1 << k;
      if (!(bitmask & visitaK)) {
          int bitmaskVisitaK = bitmask | visitaK;
          int custoAtual = mapa[pos][k] + obterMenorCaminhoHamilt(cidInicial, bitmaskVisitaK, k, mapa, memo);
          menorProxCidade = custoAtual > menorProxCidade ? menorProxCidade : custoAtual;
      }
    }

    return memo[bitmask][pos] = menorProxCidade;
}
int main(void) {

  int N;
  cin >> N;
  // cout << bitset<8>(127) << endl;

  int comeco;
  cin >> comeco;

  v2i memo(1 << N, vi(N, -1));
  v2i matrizMapa = obterEntradas(N);

  int bmVisita0 = 1 << comeco;
  cout << obterMenorCaminhoHamilt(comeco, bmVisita0, comeco, matrizMapa, memo) << endl;

  // printV2i(matrizMapa);
  // printV2Bitmask(memo);

}