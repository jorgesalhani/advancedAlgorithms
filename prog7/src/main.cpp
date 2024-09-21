/**
 * Projeto 7: Labirinto
 * 
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vecInt;
typedef vector<vecInt> array2d;

void imprimirLabirinto(array2d labirinto) {
  int M = labirinto.size();
  int N = labirinto[0].size();
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cout << labirinto[i][j] << " ";
    }
    cout << endl;
  }
}

array2d construirLabirinto(int M, int N) {
  array2d labirinto(M+2, vector<int>(N+2));

  for (int i = 0; i < M+2; i++) {
    for (int j = 0; j < N+2; j++) {
      labirinto[i][j] = 0;

      if (i == 0 || i == M+1) labirinto[i][j] = 1;
      if (j == 0 || j == N+1) labirinto[i][j] = 1;
    }
  }

  labirinto[1][1] = 2;
  labirinto[M][N] = 3;

  string buff;
  getline(cin, buff);
  getline(cin, buff);
  while (buff.size() > 1) {
    int x, y;

    x = (int) buff[0] - 47;
    y = (int) buff[2] - 47;
    labirinto[x][y] = 1;

    getline(cin, buff);
  }

  return labirinto;
}

int totalCaminhos = 0;
vecInt distancias;

bool encontrarSaida(array2d &labirinto, vecInt coordAtual, int &contadorPassos) {

  int M = labirinto.size();
  int N = labirinto[0].size();

  vecInt saida = {M-2, N-2};

  if (coordAtual[0] == saida[0] && coordAtual[1] == saida[1]) {
    totalCaminhos++;
    // cout << "AQUI!!" << endl;
    distancias.push_back(contadorPassos);
    --contadorPassos;
    return true;
  }

  // imprimirLabirinto(labirinto);
  // cout << contadorPassos << endl;

  vecInt baiCoordProx = {coordAtual[0] + 1, coordAtual[1]};
  vecInt dirCoordProx = {coordAtual[0], coordAtual[1] + 1};
  vecInt cimCoordProx = {coordAtual[0] - 1, coordAtual[1]};
  vecInt esqCoordProx = {coordAtual[0], coordAtual[1] - 1};

  bool baiLivre = labirinto[baiCoordProx[0]][baiCoordProx[1]] != 1;
  bool dirLivre = labirinto[dirCoordProx[0]][dirCoordProx[1]] != 1;
  bool cimLivre = labirinto[cimCoordProx[0]][cimCoordProx[1]] != 1;
  bool esqLivre = labirinto[esqCoordProx[0]][esqCoordProx[1]] != 1;

  if (!baiLivre && !dirLivre && !cimLivre && !esqLivre) {
    --contadorPassos;
    labirinto[coordAtual[0]][coordAtual[1]] = 0;
    return false;
  }

  labirinto[coordAtual[0]][coordAtual[1]] = 1;

  // cout << "(" << coordAtual[0] << "," << coordAtual[1] << ")" << " -> ";
  // cout << baiLivre << dirLivre << cimLivre << esqLivre << endl;

  if (baiLivre) {
    encontrarSaida(labirinto, baiCoordProx, ++contadorPassos);
  }
  if (dirLivre) {
    encontrarSaida(labirinto, dirCoordProx, ++contadorPassos);
  }
  if (cimLivre) {
    encontrarSaida(labirinto, cimCoordProx, ++contadorPassos);
  }
  if (esqLivre) {
    encontrarSaida(labirinto, esqCoordProx, ++contadorPassos);
  }

  --contadorPassos;
  labirinto[coordAtual[0]][coordAtual[1]] = 0;
  
  return false;
}

int main(void) {
  int M, N;
  cin >> M;
  cin >> N;

  int contPassos = 0;
  array2d labirinto = construirLabirinto(M, N);
  encontrarSaida(labirinto, {1,1}, contPassos);  
  sort(distancias.begin(), distancias.end());
  cout << totalCaminhos << " " << distancias[0] << endl;
  
  return 0;
}