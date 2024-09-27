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

  if (i == 0) return memo[i] = 0;
  long int ci1 = abs(custos[i-1] - custos[i]);
  if (i == 1) 
    return memo[i] = abs(custos[i-1] - custos[i]);
  
  long int ci2 = abs(custos[i-2] - custos[i]);

  memo[i] = min(ci2 + calcularMenorCusto(custos, i-2), ci1 + calcularMenorCusto(custos, i-1));
  return memo[i];
}


int main(void) {

  long int N;
  cin >> N;

  vecLongInt custos = obterEntradas(N);
  cout << calcularMenorCusto(custos, N-1) << endl;

  return 0;
}