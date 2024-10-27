#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#define N_MAX_PRIMOS 10000000

using namespace std;

typedef vector<long long int> vi;
typedef vector<vi> v2i;
typedef map<int,int> mii;


vi obterValoresEntrada(int N) {
  vi valoresEntrada;

  for (int j = 0; j < N; j++) {
    int val;
    cin >> val;
    valoresEntrada.push_back(val);
  }
  return valoresEntrada;
}

vi montarCrivoVetorPrimos(long long int maxPrimos){
  vi primos;

  bitset<N_MAX_PRIMOS> crivo;
	crivo.set();

	crivo[0] = crivo[1] = 0;

	for (long long int i = 2; i <= maxPrimos + 1; ++i){
		if (crivo[i]){
			for (long long int j = i*i; j <= maxPrimos + 1; j += i) {
				crivo[j]=0;
      }
      primos.push_back((int)i);
		}
	}

  return primos;
}

void printMap(mii &kv) {
  for (auto &item : kv) {
    cout << item.first << " -> " << item.second << endl;
  }
}

mii fatoresPrimosMap(long long int N, vi &primos){
	mii fatMap;

	for (int i = 0, fp = primos[i]; fp*fp <=N; i++, fp = primos[i]){
		while (N % fp == 0){
			N = N/fp;
			fatMap[fp]++;
		}
	}
  
	if (N != 1)
		fatMap[N] = 1;

	return fatMap;
}

int obterTotalFatoresPrimos(mii fatoresPrimos) {
  int totalFatPrim = 1;
  for (auto &x : fatoresPrimos) {
    totalFatPrim *= x.second + 1;
  }

  return totalFatPrim;
}

int main(void) {

  int N;
  cin >> N;

  vi primos = montarCrivoVetorPrimos(N_MAX_PRIMOS);

  vi valores = obterValoresEntrada(N);

  for (auto &x : valores) {
    mii fatoresPrimos = fatoresPrimosMap(x, primos);
    cout << obterTotalFatoresPrimos(fatoresPrimos) << endl;
  }
  

  return 0;
}