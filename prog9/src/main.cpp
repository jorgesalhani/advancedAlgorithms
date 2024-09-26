#include <iostream>
#include <vector>
#include <cstdio>
#include <unordered_map>

using namespace std;

typedef vector<long int> vecLongInt;

vecLongInt memo;

vecLongInt obterEntradas(long int N) {
  vecLongInt custos;
  for (long int i = 0; i < N; i++) {
    long int custo;
    cin >> custo;
    custos.push_back(custo);

    memo.push_back(-1);
  }

  return custos;
}

long int calcularMenorCusto(vecLongInt custos, long int i) {

  if (memo[i] != -1) return memo[i];

  if (i == 0) return custos[i];
  if (i == 1) 
    return memo[i] = abs(custos[i-1] - custos[i]);
  
  long int ci1 = abs(custos[i-1] - custos[i]);
  long int ci2 = abs(custos[i-2] - custos[i]);
  long int prox = ci1 <= ci2 ? i-1 : i-2;
  memo[i] = min(ci1, ci2) + min(calcularMenorCusto(custos, prox), calcularMenorCusto(custos, i-1));

  for (auto &x : memo) cout << x << ", ";
  cout << endl;

  return memo[i];
}


int main(void) {

  long int N;
  cin >> N;

  vecLongInt custos = obterEntradas(N);

  for (auto &x : custos) cout << x << " ";
  cout << endl;

  cout << calcularMenorCusto(custos, N-1) << endl;

  return 0;
}