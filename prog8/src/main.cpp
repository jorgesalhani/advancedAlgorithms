#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vecInt;
typedef map<int, vecInt> mapIntToVec;
typedef vector<mapIntToVec> vecMaps;
typedef vector<vecInt> vecVecInt;

vecMaps obterEntradasComoMapas() {
  vecMaps listaMapas;
  
  int nVertices, nArestas;
  int origem, destino;

  cin >> nVertices;
  cin >> nArestas;

  while (nVertices != 0 && nArestas != 0) {
    mapIntToVec mapa;

    for (int i = 0; i < nVertices; i++) mapa[i] = {};

    for (int i = 0; i < nArestas; i++) {
      cin >> origem;
      cin >> destino;

      mapa[origem].push_back(destino);
      mapa[destino].push_back(origem);
    }

    listaMapas.push_back(mapa);

    cin >> nVertices;
    cin >> nArestas;
  }

  return listaMapas;
}

void imprimirMapas(vecMaps listaMapas) {
  for (auto &lm : listaMapas) {
    for (auto &m : lm) {
      cout << m.first << " -> ";
      for (auto &x : m.second) cout << x << ", ";
      cout << endl;
    }
    cout << endl;
  }
}

void prosseguirPara(mapIntToVec mapa, int origem, int destino, vecVecInt &arestasVisitada, vecVecInt &caminho) {
  if (!destino && destino != 0) return;

  caminho.push_back({origem, destino});
  for (auto &visit : arestasVisitada) {
    if ((visit[0] == destino && visit[1] == origem) ||
        (visit[0] == origem && visit[1] == destino)) {
      // cout << "POP2: " << caminho[caminho.size()-1][0] << "," << caminho[caminho.size()-1][1] <<endl;
      caminho.pop_back();
      // arestasVisitada.pop_back();
      // for (auto &x : caminho) cout << "(" << x[0] << "," << x[1] << ")" << "-";
      return;
    }
  }

  arestasVisitada.push_back({origem, destino});
  // caminho.push_back({origem, destino});
  // for (auto &x : caminho) cout << "(" << x[0] << "," << x[1] << ")" << "-";

  for (auto &proxDest : mapa[destino]) {
    prosseguirPara(mapa, destino, proxDest, arestasVisitada, caminho);
    // cout << destino << "," << proxDest << endl;
  }

  // cout << endl << origem << "," << destino << " -- (+TOT) " << endl;
}

int removerDeadends(vecVecInt &caminho) {
  int maximo = 1;
  // mapIntToVec caminhos;

  // int caminhoTotal = caminho.size();
  // for (int i = 1; i < (int) caminhoTotal; i++) {
  //   int moveI = i;
  //   for (int j = 1; j < (int) caminhoTotal; j++) {
  //     if (caminho[moveI-1][1] == caminho[j][0]) {
  //       cout << caminho[j][0]<< "," << caminho[j][1] << "; ";
  //       // caminhos[moveI-1].push_back(caminho[j][0]);
  //       moveI++;
  //     }
  //   }
  //   // cout << endl;
  // }

  sort(caminho.begin(), caminho.end(), [](vecInt a, vecInt b) { return a[1] == b[0]; } );
  // for (auto &x : caminho) cout << x[0] << "," << x[1] << "; " << endl;
  // cout << endl;

  int temp = 1;
  for (int i = 1; i < (int) caminho.size(); i++) {
    cout << i << ": " << caminho[i-1][0] << "," << caminho[i-1][1] << " = " << caminho[i][0] << "," << caminho[i][1] << " --> ";
    cout << (caminho[i-1][1] == caminho[i][0]);
    if (caminho[i-1][1] == caminho[i][0]) temp++;
    else {
      temp = 1; 
    }
    cout << " -> " << temp << endl;
  }

  maximo = temp;

  // for (auto &m : caminhos) {
  //   cout << m.second.size() << " - ";
  //   maximo = m.second.size() > maximo ? m.second.size() : maximo;
  // }
  // cout << endl;

  return maximo;
}

int encontrarMaiorCaminho(mapIntToVec mapa) {
  vecVecInt arestasVisitada;
  vecVecInt caminho;
  for (auto &aresta : mapa) {
    if (aresta.second.size() == 0) continue;
    prosseguirPara(mapa, aresta.first, aresta.second[0], arestasVisitada, caminho);
  }

  for (auto &x : caminho) cout << "(" << x[0] << "," << x[1] << ")" << "-";
  cout << endl;
  int maximo = removerDeadends(caminho);

  return maximo;
}


int main() {

  vecMaps listaMapas = obterEntradasComoMapas();
  // imprimirMapas(listaMapas);
  cout << endl;
  for (auto &mapa : listaMapas) {
    int maiorCaminho = encontrarMaiorCaminho(mapa);
    cout << maiorCaminho << endl;
  }


  return 0;
}