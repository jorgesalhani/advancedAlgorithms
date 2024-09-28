#include <iostream>
#include <vector>

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

long int calcularMenorCusto(vecLongInt *endCustos, long int i) {
  vecLongInt custos = *endCustos;

  if (memo[i] != -1) return memo[i];

  if (i == 0) return memo[i] = 0;
  long int ci1 = abs(custos[i-1] - custos[i]);
  if (i == 1) 
    return memo[i] = ci1;
  
  long int ci2 = abs(custos[i-2] - custos[i]);
  memo[i] = min(ci2 + calcularMenorCusto(endCustos, i-2), ci1 + calcularMenorCusto(endCustos, i-1));
  return memo[i];
}

int main(void) {

  long int N;
  cin >> N;

  vecLongInt custos = obterEntradas(N);
  // for (auto &x : memo) cout << x << " ";
  // cout << endl;
  cout << calcularMenorCusto(&custos, N-1) << endl;
  // for (auto &x : memo) cout << x << " ";
  // cout << endl;

  return 0;
}