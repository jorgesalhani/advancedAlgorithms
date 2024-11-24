#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

int obterRaizes(int i, int N) {
  return i*i % N - 1;
}

int main() {

  int N;
  cin >> N;

  vi res = vi(N, -1);

  for (int i = 0; i < N; i++) {
    int raiz = obterRaizes(i, N);
    res[raiz] = raiz;
  }

  for (auto &x : res) cout << x << " ";
  cout << endl;

  return 0;
}