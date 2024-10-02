#include <iostream>
#include <vector>
#define NMAX 50005

using namespace std;

typedef vector<int> vecInt;

vecInt obterEntradas(int N) {
  vecInt custos;
  for (int i = 0; i < N; i++) {
    int c;
    cin >> c;
    custos.push_back(c);
  }

  return custos;
}

int obterMenorSalto(int i, int j, vecInt &custos, vecInt &memo) {
  if (memo[i] != -1) return memo[i];

  cout << i << " " << j << " " << custos[i] << " " << memo[j] << endl;
  if (abs(j - i) > custos[j]) return 10000;

  if (i == 1) return memo[i] = 1;


  memo[i] = min(obterMenorSalto(i-1, i-1, custos, memo) + 1, obterMenorSalto(i, j-1, custos, memo) + 1);
  cout << j << "-> " << memo[i] << "; " << endl;

  return memo[i];
}


int main(void) {

  int N;
  cin >> N;

  vecInt custos = obterEntradas(N);
  vecInt memo;
  memo.assign(N+1, -1);
  
  for (auto &x : custos) cout << x << " ";
  cout << endl;

  cout << obterMenorSalto(N-1, N-1, custos, memo) << endl;

  for (auto &x : memo) cout << x << " ";
  cout << endl;

  return 0;
}