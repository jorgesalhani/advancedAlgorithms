#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> vi;

vi obterLpsKMP(string &padrao) {
    int m = padrao.size();
    vi lps(m, 0);
    
    int tamMaiorPrefSuf = 0;
    int i = 1;
    while (i < m) {
      if (padrao[i] == padrao[tamMaiorPrefSuf]) {
        tamMaiorPrefSuf++;
        lps[i] = tamMaiorPrefSuf;
        i++;
        // cout << tamMaiorPrefSuf << "; ";
      } else {
        if (tamMaiorPrefSuf != 0) {
          tamMaiorPrefSuf = lps[tamMaiorPrefSuf - 1];
        } else {
          lps[i] = 0;
          i++;
        }
        // cout << "p[i] = " << padrao[i] << " --- p[tamLPS] = " << padrao[tamMaiorPrefSuf] << endl;
      }
    }

    return lps;
}

vi KMPSearch(string &texto, string &padrao, vi &lps) {
    vi positions; 
    int n = texto.size();
    int m = padrao.size();
    
    int i = 0;
    int j = 0;

    while (i < n) {
      if (texto[i] == padrao[j]) {
        i++;
        j++;
      }
      if (j == m) {
        positions.push_back(i - j);
        j = lps[j - 1];
        // cout << j << " - ";
      } else 
      if (i < n && texto[i] != padrao[j]) {
        if (j != 0) {
          j = lps[j - 1];
        } else {
          i++;
        }
      }
    }

    return positions;
}

int main() {
    string texto, padrao;
    cin >> texto >> padrao;

    vi lps = obterLpsKMP(padrao);
    
    // for (auto &x : lps) cout << x << " ";
    // cout << endl;

    vi res = KMPSearch(texto, padrao, lps);

    cout << res.size() << endl;

    if (res.size() < 100) {
      for (auto &x : res) cout << x << endl;
    }

    return 0;
}
