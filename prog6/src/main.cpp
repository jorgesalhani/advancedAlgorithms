/**
 * Projeto 6: Livros
 * 
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
typedef vector<int> vecInt;

vecInt obterPaginasPorLivro(int nLivros) {
  vecInt pgsPorLivro;

  for (int i = 0; i < nLivros; i++) {
    int pgs;
    cin >> pgs;
    pgsPorLivro.push_back(pgs);
  }

  return pgsPorLivro;
}

int main() {

  int nLivros, mPessoas;
  cin >> nLivros;
  cin >> mPessoas;

  vecInt pgsPorLivro = obterPaginasPorLivro(nLivros);
  sort(pgsPorLivro.begin(), pgsPorLivro.end(), [](int a, int b) { return b < a; });

  vecInt menoresPgs = vecInt(pgsPorLivro.begin() + mPessoas - 1, pgsPorLivro.end());

  long int somaMenores = reduce(menoresPgs.begin(), menoresPgs.end(), 0);
  long int maxDentreAlocacoes = somaMenores > pgsPorLivro[0] ? somaMenores : pgsPorLivro[0];

  // cout << maxDentreAlocacoes;
  for (auto &x : menoresPgs) cout << x << " ";
  cout << endl;

  return 0;
}