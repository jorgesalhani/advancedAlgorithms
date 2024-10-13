#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef vector<string> vs;
typedef vector<char> vc;

typedef stack<string> ss;

typedef vector<int> vi;
typedef vector<vector<int>> v2i;
typedef vector<vs> v2s;

vs obterEntradas() {
  string s1;
  cin >> s1;

  string s2;
  cin >> s2;

  return {s1, s2};
}

int custoEdit(char c1, char c2) {
  if (c1 == c2) return 0;

  string vogais = "aeiouAEIOU";
  bool c1vogal = vogais.find(c1);
  bool c2vogal = vogais.find(c2);
  
  if ((c1vogal && c2vogal) || (!c1vogal && !c2vogal)) return 1;

  return 3;
}

void printMemo(vs palavras, v2i memo) {
  string s1 = palavras[0];
  string s2 = palavras[1];
  cout << "x - ";
  for (auto &c2 : s2) cout << c2 << " ";
  cout << endl;

  int i = -1;
  for (auto &xi : memo) {
    if (i == -1) cout << "- ";
    else cout << s1[i] << " ";
    for (auto &x : xi) cout << x << " ";
    cout << endl;
    i++;
  }
  cout << endl;
}

void printMemoOps(v2i memo, v2s memoOps) {
  int i = memo.size() - 1;
  int j = memo[0].size() - 1;

  ss pilhaOps;

  while (i > 0 || j > 0) {
    pilhaOps.push(memoOps[i][j]);

    int cima = memo[i-1][j];
    int lado = memo[i][j-1];
    int diag = memo[i-1][j-1];

    int minAteAqui = min({cima,lado,diag});

    if (minAteAqui == cima) {
      i--;
    } else 
    if (minAteAqui == lado) {
      j--;
    } else {
      i--;
      j--;
    }
  }

  while (!pilhaOps.empty()) {
    if (pilhaOps.top() == "X") {
      pilhaOps.pop();
      continue;
    }
    cout << pilhaOps.top();
    pilhaOps.pop();
  }
}

int obterMenorCustoEditDist(vs palavras, int i, int j, v2i &memo, v2s &memoOperacoes) {

  string s1 = palavras[0];
  string s2 = palavras[1];

  if (i == 0) return memo[i][j] = j*2;
  if (j == 0) return memo[i][j] = i*2;

  if (memo[i][j] != -1) return memo[i][j];

  int custoEditAtual = custoEdit(s1[i-1], s2[j-1]);

  int casoAvancarEmS1 = obterMenorCustoEditDist(palavras, i-1, j, memo, memoOperacoes) + 2;
  int casoAvancarEmS2 = obterMenorCustoEditDist(palavras, i, j-1, memo, memoOperacoes) + 2;
  int casoAvancarAmbos = obterMenorCustoEditDist(palavras, i-1, j-1, memo, memoOperacoes) + custoEditAtual;

  auto menorCusto = min({casoAvancarEmS1, casoAvancarEmS2, casoAvancarAmbos});
  memo[i][j] = menorCusto;

  string memoOpRes;
  // cout << menorCusto;
  if (custoEditAtual == 0) {
    memoOpRes = "X";
  } else
  if (menorCusto == casoAvancarEmS1) {
    memoOpRes = "R:" + string(1, s1[i-1]);
  } else
  if (menorCusto == casoAvancarEmS2) {
    memoOpRes = "I:" + string(1, s2[j-1]);
  } else
  if (menorCusto == casoAvancarAmbos) {
    memoOpRes = "T:" + string(1, s1[i-1]) + '-' + string(1, s2[j-1]);
  }

  memoOperacoes[i][j] = memoOpRes;
  return memo[i][j];
}

int main(void) {

  vs palavras = obterEntradas();

  int N1, N2;
  N1 = palavras[0].size();
  N2 = palavras[1].size();

  v2i memo(N1+1, vector<int>(N2+1, -1));
  v2s memoOperacoes(N1+1, vs(N2+1, ""));

  int resultado = obterMenorCustoEditDist(palavras, N1, N2, memo, memoOperacoes);
  cout << resultado << endl;

  // printMemo(palavras, memo);
  if (resultado != 0) printMemoOps(memo, memoOperacoes);
  else cout << "nada a fazer" << endl;

  return 0;
}