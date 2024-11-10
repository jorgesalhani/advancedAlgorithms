#include <iostream>

typedef unsigned long long int lli;

lli P = 1000000007;
using namespace std;

lli obterExponencial(lli b, lli e, lli modP) {
  lli prod = 1;
  lli cur = b;
  lli q = e;
  while (q > 0) {
    if (q % 2 == 1) {
      prod = (cur * prod) % modP;
      q--;
    }
    cur = (cur * cur) % modP;
    q = (lli) q / 2;
  }

  return prod;
}

int main() {

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    lli b, e1, e2;
    cin >> b >> e1 >> e2;
    lli reducedExp = obterExponencial(e1, e2, P-1);
    lli res = obterExponencial(b, reducedExp, P);
    cout << res << endl;
  }

  return 0;
}