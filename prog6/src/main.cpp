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
typedef vector<long int> vecLongInt;

vecLongInt cumulativoCresc;
vecLongInt cumulativoDecresc;

vecLongInt obterPaginasPorLivro(long int nLivros) {
  vecLongInt pgsPorLivro;

  for (long int i = 0; i < nLivros; i++) {
    long int pgs;
    cin >> pgs;
    pgsPorLivro.push_back(pgs);
  }

  sort(pgsPorLivro.begin(), pgsPorLivro.end(), [](long int a, long int b) { return a < b; });

  long int cumCresc = 0;
  long int cumDecresc = 0;

  long int j = nLivros - 1;

  for (long int i = 0; i < nLivros; i++) {
    cumCresc += pgsPorLivro[i];
    cumDecresc += pgsPorLivro[j];

    cumulativoCresc.push_back(cumCresc);
    cumulativoDecresc.push_back(cumDecresc);
    j--;
  }

  for (auto &x : cumulativoCresc) cout << x << " ";
  cout << endl;

  for (auto &x : cumulativoDecresc) cout << x << " ";
  cout << endl;

  return pgsPorLivro;
}


long int obterDivisaoBalanceada(vecLongInt pgsPorLivro) {
  long int meio = (long int) (pgsPorLivro.size() / 2);

  if (meio == 0) {
    return 0;
  }

  vecLongInt pgsPorLivroCrescEsq = vecLongInt(pgsPorLivro.begin(), pgsPorLivro.end() - meio);
  obterDivisaoBalanceada(pgsPorLivroCrescEsq);

  long int totalPgsPorLivroEsq = reduce(pgsPorLivroCrescEsq.begin(), pgsPorLivroCrescEsq.end(), 0);

  vecLongInt pgsPorLivroDir = vecLongInt(pgsPorLivro.begin() + meio, pgsPorLivro.end());
  obterDivisaoBalanceada(pgsPorLivroDir);

  long int totalPgsPorLivroDir = reduce(pgsPorLivroDir.begin(), pgsPorLivroDir.end(), 0);

  long int menorDosMaiores = totalPgsPorLivroEsq < totalPgsPorLivroDir ? totalPgsPorLivroEsq : totalPgsPorLivroDir;

  return menorDosMaiores;
}

int main() {

  long int nLivros, mPessoas;
  cin >> nLivros;
  cin >> mPessoas;

  vecLongInt pgsPorLivro = obterPaginasPorLivro(nLivros);
  long int totalBalanceado = obterDivisaoBalanceada(pgsPorLivro);

  cout << totalBalanceado << endl;

  return 0;
}